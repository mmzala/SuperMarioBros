#include "Mario.h"
#include "Components/Transform.h"
#include "../../Utils/Math.h" // FindClosest

// Graphics
#include "../../Engine/Graphics/Sprite.h" // Rendering sprite
#include "../../Engine/Graphics/Animator.h" // Playing animations
#include "../Data/Animations.h" // Animations data

// Controlling character
#include "../../Engine/Input/Input.h" // Checking input
#include "Components/MovementComponent.h" // Character controller
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h" // Camera follow

// Collision Checking
#include "../../Engine/Physics/RectBounds.h" // Getting rect bounds for collision
#include "../../Engine/Physics/CharacterCollider.h" // Ignoring collision when powering down

// Responses from collision
#include "Mushroom.h" // Power up
#include "Goomba.h" // Enemy

Mario::Mario(MarioSettings settings)
	:
	Character::Character(settings),
	camera(SMBEngine::GetInstance()->GetCamera()),
	movementComponent(new MovementComponent(this, settings.movementSettings)),
	marioState(MarioState::Dead),
	marioPowerState(MarioPowerState::Dead),
	poweringUpTime(settings.poweringUpTime),
	poweringDownTime(settings.poweringDownTime),
	poweringDownFlickeringSpeed(settings.poweringDownFlickeringSpeed),
	powerChangeTimer(0.0f),
	powerChangeAnimationTimer(0.0f)
{
	// Getting animations data
	animations = std::unordered_map<MarioPowerState, std::vector<Animation>> {
		{MarioPowerState::Small, Animations::Mario::Small::sMario},
		{MarioPowerState::Large, Animations::Mario::Large::lMario},
		{MarioPowerState::Fire, Animations::Mario::Large::fMario},
	};

	camera->SetBoundary(tilemap->GetTilemapBounds());
	UpdateState(MarioState::Controlling);
	UpdatePowerState(MarioPowerState::Small);
	UpdateAnimations();
}

Mario::~Mario()
{
	delete movementComponent;
}

void Mario::Update(const float deltaTime)
{
	switch (marioState)
	{
	case MarioState::Controlling:
		Move(deltaTime);
		UpdateCameraFollow();
		UpdateAnimations();
		animator->Update(deltaTime);
		sprite->Draw(transform->GetWorldMatrix());
		break;

	case MarioState::PowerUp:
		PowerUpAnimation(deltaTime);
		sprite->Draw(transform->GetWorldMatrix());
		break;

	case MarioState::PowerDown:
		Move(deltaTime);
		UpdateCameraFollow();
		PowerDownAnimation(deltaTime);
		animator->Update(deltaTime);
		break;

	case MarioState::Dead:
		sprite->Draw(transform->GetWorldMatrix());
	}
}

MarioState Mario::GetMarioState()
{
	return marioState;
}

void Mario::Move(const float deltaTime)
{
	Input* input = Input::GetInstance();
	
	MovementInput movementInput = MovementInput();
	movementInput.left = input->GetKey(DIK_LEFTARROW) || input->GetKey(DIK_A);
	movementInput.right = input->GetKey(DIK_RIGHTARROW) || input->GetKey(DIK_D);
	movementInput.run = input->GetKey(DIK_Z) || input->GetKey(DIK_M);
	movementInput.jump = input->GetKey(DIK_SPACE);

	movementComponent->Update(movementInput, deltaTime);
	Character::Move(deltaTime);
}

void Mario::CheckCollision(const float deltaTime)
{
	Character::CheckCollision(deltaTime);

	// Making sure the player cannot go back
	Rect viewport = camera->GetViewportBounds();
	DirectX::XMFLOAT2 deltaVelocity = DirectX::XMFLOAT2(velocity.x * deltaTime, velocity.y * deltaTime);
	Rect playerBounds = bounds->GetBoundsWithOffset(deltaVelocity);

	if (viewport.x > playerBounds.x)
	{
		velocity.x = 0.0f;
	}

	HandleHeadCollision();
}

void Mario::OnTileHit(CheckSide side, int tileType, DirectX::XMINT2 tilemapPosition, DirectX::XMFLOAT2 worldPosition)
{
	switch (side)
	{
	case CheckSide::Top:
		headCollisionPositions.push_back(tilemapPosition);
		break;
	}
}

void Mario::OnCharacterHit(Character* other)
{
	// Can't use a switch :(
	if (dynamic_cast<Goomba*>(other))
	{
		Rect otherBounds = other->bounds->GetBounds();
		if (bounds->GetBounds().y > (otherBounds.y + otherBounds.height))
		{
			other->isActive = false;
			movementComponent->ForceJump();
		}
		else
		{
			UpdatePowerState((MarioPowerState)((int)marioPowerState - 1));
		}
	}
	else if (dynamic_cast<Mushroom*>(other))
	{
		UpdatePowerState(MarioPowerState::Large);
		other->isActive = false;
	}
}

void Mario::HandleHeadCollision()
{
	if (headCollisionPositions.size() == 0) return;
	DirectX::XMINT2 hitTile = GetHeadCollisionTile();
	
	switch (tilemap->GetTileType(hitTile))
	{
	case 2:
		if (marioPowerState == MarioPowerState::Small) break;
		tilemap->BreakTile(hitTile);
		break;
	default:
		tilemap->CheckForTileAction(hitTile);
		break;
	}

	headCollisionPositions.clear();
}

void Mario::UpdateCameraFollow()
{
	DirectX::XMFLOAT2 viewportCenter = camera->GetViewportCenter();

	if (viewportCenter.x < transform->position.x)
	{
		camera->FollowPosition(transform->position, true, false);
	}
	camera->FollowPosition(transform->position, true, false);
}

void Mario::UpdateAnimations()
{
	// If the players dies (gets hit by enemy) animation update happens once, we set the game over animation
	switch (marioState)
	{
	case MarioState::Dead:
		animator->SetAnimation(animations[MarioPowerState::Small][Animations::Mario::Small::SAnimationState::GameOver]);
	case MarioState::PowerUp: // Animation for powering up is handled somewhere else
		return;
	}

	UpdateMovementAnimations(marioPowerState);
}

void Mario::UpdateMovementAnimations(MarioPowerState marioPowerState)
{
	switch (movementComponent->GetState())
	{
	case MovementState::Standing:
		animator->SetAnimation(animations[marioPowerState][Animations::Mario::AnimationState::Standing]);
		break;
	case MovementState::Running:
		animator->SetAnimation(animations[marioPowerState][Animations::Mario::AnimationState::Walking]);
		break;
	case MovementState::TurningAround:
		animator->SetAnimation(animations[marioPowerState][Animations::Mario::AnimationState::ChangeDir]);
		break;
	case MovementState::Jumping:
		animator->SetAnimation(animations[marioPowerState][Animations::Mario::AnimationState::Jumping]);
		break;
	}

	switch (movementComponent->GetMovementDirection())
	{
	case 1:
		sprite->FlipSpriteX(false);
		break;
	case -1:
		sprite->FlipSpriteX(true);
		break;
	}
}

void Mario::PowerUpAnimation(const float deltaTime)
{
	powerChangeTimer -= deltaTime;
	powerChangeAnimationTimer += animations[marioPowerState][Animations::Mario::Large::LAnimationState::Transitional].speed * deltaTime;

	if (powerChangeAnimationTimer > 1.0f)
	{
		sprite->GetFrame() == animations[marioPowerState][Animations::Mario::Large::LAnimationState::Transitional].startFrame ?
			sprite->SetFrame(animations[MarioPowerState::Small][Animations::Mario::AnimationState::Standing].startFrame) :
			sprite->SetFrame(animations[marioPowerState][Animations::Mario::Large::LAnimationState::Transitional].startFrame);
		powerChangeAnimationTimer = 0.0f;
	}

	if (powerChangeTimer <= 0.0f) UpdateState(MarioState::Controlling);
}

void Mario::PowerDownAnimation(const float deltaTime)
{
	powerChangeTimer -= deltaTime;
	powerChangeAnimationTimer += poweringDownFlickeringSpeed * deltaTime;

	if (powerChangeAnimationTimer < 0.5f)
	{
		sprite->Draw(transform->GetWorldMatrix());
	}
	else if (powerChangeAnimationTimer > 1.0f)
	{
		powerChangeAnimationTimer = 0.0f;
	}

	powerChangeTimer > 0.5f ? UpdateMovementAnimations((MarioPowerState)((int)marioPowerState + 1)) : UpdateAnimations();
	if (powerChangeTimer <= 0.0f)
	{
		characterCollider->RemoveCharacterTypeToIgnore<Goomba>();
		characterCollider->RemoveCharacterTypeToIgnore<Mushroom>();
		UpdateState(MarioState::Controlling);
	}
}

void Mario::UpdateState(MarioState marioState)
{
	if (this->marioState == marioState) return;
	this->marioState = marioState;

	switch (marioState)
	{
	case MarioState::PowerUp:
		powerChangeTimer = poweringUpTime;
		powerChangeAnimationTimer = 0.0f;
		break;

	case MarioState::PowerDown:
		characterCollider->AddCharacterTypeToIgnore<Goomba>();
		characterCollider->AddCharacterTypeToIgnore<Mushroom>();
		powerChangeTimer = poweringDownTime;
		powerChangeAnimationTimer = 0.0f;
		break;
	}
}

void Mario::UpdatePowerState(MarioPowerState marioPowerState)
{
	if (this->marioPowerState == marioPowerState) return;

	switch (marioPowerState)
	{
	case MarioPowerState::Dead:
		UpdateState(MarioState::Dead);
		return;

	case MarioPowerState::Small:
		// Updating collider size for small Mario
		bounds->SetSizeOffset(DirectX::XMFLOAT2(0.0f, -(sprite->GetSize().y / 2)));
		break;

	default:
		// Updating collider size for large Mario
		bounds->SetSizeOffset(DirectX::XMFLOAT2(0.0f, 0.0f));
		break;
	}

	if (this->marioPowerState != MarioPowerState::Dead && marioPowerState != MarioPowerState::Dead)
	{
		(int)this->marioPowerState > (int)marioPowerState ? UpdateState(MarioState::PowerDown) : UpdateState(MarioState::PowerUp);
	}
	this->marioPowerState = marioPowerState;
}

DirectX::XMINT2 Mario::GetHeadCollisionTile()
{
	int size = static_cast<int>(headCollisionPositions.size());
	int* xPositions = new int[size];
	for (int i = 0; i < size; i++)
	{
		xPositions[i] = static_cast<int>(headCollisionPositions[i].x);
	}
	float playerPosX = tilemap->GetPositionInTilemapCoordinates(transform->position).x;
	int closestTileX = Math::FindClosest(xPositions, size, static_cast<int>(playerPosX));

	delete[] xPositions;
	return DirectX::XMINT2(closestTileX, headCollisionPositions[0].y); // Y position is the same for all vector elements
}


