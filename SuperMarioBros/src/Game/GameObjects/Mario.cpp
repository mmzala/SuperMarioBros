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

// Adding score
#include "../Game.h" // Getting ScoreTracker
#include "../Scoring/ScoreTracker.h"
#include "../Data/ScoreData.h"

int Mario::lives = 3;

Mario::Mario(MarioSettings settings)
	:
	Character::Character(settings),
	camera(SMBEngine::GetInstance()->GetCamera()),
	scoreTracker(SMBEngine::GetInstance()->GetGame()->GetScoreTracker()),
	movementComponent(new MovementComponent(this, settings.movementSettings)),
	marioState(MarioState::Dead),
	marioPowerState(MarioPowerState::Dead),
	poweringUpTime(settings.poweringUpTime),
	poweringDownTime(settings.poweringDownTime),
	poweringDownFlickeringSpeed(settings.poweringDownFlickeringSpeed),
	powerChangeTimer(0.0f),
	powerChangeAnimationTimer(0.0f),
	flagPoleBottomPositionY(settings.flagPoleBottomPositionY),
	poleDescendingSpeed(settings.poleDescendingSpeed),
	startPolePositionY(0.0f),
	poleDescentInterpolationValue(0.0f),
	deathAnimationSpeed(settings.deathAnimationSpeed),
	deathJumpSpeed(settings.movementSettings.maxJumpSpeed),
	deathJumpTime(settings.movementSettings.maxJumpTime),
	timeBeforeDeathAnimation(settings.timeBeforeDeathAnimation),
	timeAfterDeathBeforeSceneChange(settings.timeAfterDeathBeforeSceneChange)
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
	case MarioState::Dead:
		DeathAnimation(deltaTime);
		sprite->Draw(transform->GetWorldMatrix());
		break;

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
		PowerDownAnimation(deltaTime); // Drawing the sprite is a part of the power down animation
		animator->Update(deltaTime);
		break;

	case MarioState::TouchedFlagPole:
		GoToCastle(deltaTime);
		UpdateCameraFollow();
		animator->Update(deltaTime);
		sprite->Draw(transform->GetWorldMatrix());
		break;
	}
}

MarioState Mario::GetMarioState()
{
	return marioState;
}

int Mario::GetLives()
{
	return lives;
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
	switch (tileType)
	{
	case 33: // Flagpole bar
	case 34: // Flagpole top
		if (transform->position.y < worldPosition.y + tilemap->GetTileSize() / 2) break;
		OnHitFlagPole(worldPosition, tilemapPosition);
		break;

	case 11: // Castle brick (used ONLY to check if player should be in castle)
		UpdateState(MarioState::InCastle);
		isActive = false;
		break;
	}

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
	if (Enemy* enemy = dynamic_cast<Enemy*>(other))
	{
		Rect otherBounds = other->bounds->GetBounds();
		if (bounds->GetBounds().y > (otherBounds.y + otherBounds.height))
		{
			enemy->OnHeadStomp();
			movementComponent->ForceJump();
			scoreTracker->AddScore(ScoreData::PowerUpPickUp);
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
	case 2: // Brick
		if (marioPowerState == MarioPowerState::Small)
		{
			tilemap->AddTileToBounce(hitTile);
			break;
		}
		tilemap->BreakTile(hitTile);
		scoreTracker->AddScore(ScoreData::BreakingBrick);
		break;
	default:
		tilemap->AddTileToBounce(hitTile);
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

#if _DEBUG
	camera->FollowPosition(transform->position, true, false);
#endif // _DEBUG
}

void Mario::UpdateAnimations()
{
	// If the players dies (gets hit by enemy) animation update happens once, we set the game over animation
	switch (marioState)
	{
	case MarioState::Dead:
		animator->SetAnimation(animations[MarioPowerState::Small][Animations::Mario::Small::SAnimationState::GameOver]);
		return;

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

	if (movementComponent->IsGrounded())
	{
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
}

void Mario::OnHitFlagPole(DirectX::XMFLOAT2 worldPosition, DirectX::XMINT2 tilemapPosition)
{
	UpdateState(MarioState::TouchedFlagPole);
	sprite->FlipSpriteX(false); // Make sure player is facing the flag pole

	startPolePositionY = transform->position.y;
	transform->position.x = worldPosition.x;

	// Remove 4 collision tiles from the bottom of the pole, so that the player does not get stuck on them
	float poleTilemapPositionY = tilemap->GetPositionInTilemapCoordinates(DirectX::XMFLOAT2(0.0, flagPoleBottomPositionY)).y;
	int intPoleTilemapPositionY = static_cast<int>(std::roundf(poleTilemapPositionY));
	for (int i = 0; i < 4; i++)
	{
		tilemap->RemoveCollision(DirectX::XMINT2(tilemapPosition.x, intPoleTilemapPositionY - i));
	}

	flagPoleBottomPositionY += tilemap->GetTileSize() / 2; // So that player does not get stuck on the block below him
}

void Mario::GoToCastle(float deltaTime)
{
	// First move downwards on the flag pole
	if (poleDescentInterpolationValue <= 1.0f)
	{
		animator->SetAnimation(animations[marioPowerState][Animations::Mario::AnimationState::OnFlagPole]);

		transform->position.y = Math::Lerp(startPolePositionY, flagPoleBottomPositionY, poleDescentInterpolationValue);
		poleDescentInterpolationValue += poleDescendingSpeed * deltaTime;
	}
	else
	{
		MovementInput input;
		input.right = true;
		movementComponent->Update(input, deltaTime);

		Character::Move(deltaTime);
		UpdateMovementAnimations(marioPowerState);
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

void Mario::DeathAnimation(const float deltaTime)
{
	if (powerChangeTimer < timeBeforeDeathAnimation)
	{
		powerChangeTimer += deltaTime;
	}
	else if (powerChangeTimer < deathJumpTime + timeBeforeDeathAnimation)
	{
		velocity.y = std::fmin(velocity.y + gravityAcceleration * deathAnimationSpeed * deltaTime, deathJumpSpeed * deathAnimationSpeed);
		transform->position.y += velocity.y * deltaTime;

		powerChangeTimer += deltaTime * deathAnimationSpeed;
	}
	else
	{
		velocity.y = std::fmax(velocity.y - gravityAcceleration * deathAnimationSpeed * deltaTime, -(gravity * deathAnimationSpeed));
		transform->position.y += velocity.y * deltaTime;
	}

	timeAfterDeathBeforeSceneChange -= deltaTime;
	if (timeAfterDeathBeforeSceneChange < 0.0f)
	{
		Game* game = SMBEngine::GetInstance()->GetGame();
		if (lives > 0)
		{
			game->TransitionToScene(game->GetSceneIndex());
		}
		else
		{
			lives = 3;
			game->ChangeScene(Scenes::MainMenu);
		}
	}
}

void Mario::UpdateState(MarioState marioState)
{
	if (this->marioState == marioState) return;
	this->marioState = marioState;

	switch (marioState)
	{
	case MarioState::Dead:
		lives--;
		scoreTracker->stopTime = true;
		velocity = DirectX::XMFLOAT2(0.0f, 0.0f);
		powerChangeTimer = 0.0f;
		break;

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


