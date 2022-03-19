#include "Mario.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h" // Camera follow
#include "../../Engine/Input/Input.h" // Checking input
#include "../../Engine/Physics/RectCollider.h" // Collider
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision
#include "../Data/Animations.h" // Animations data
#include "Components/MovementComponent.h"

Mario::Mario(MarioSettings settings)
	:
	Character::Character(CharacterSettings(settings.spriteSettings, settings.tilemap, settings.walkingSpeed, settings.gravity)),
	camera(SMBEngine::GetInstance()->GetCamera()),
	movementComponent(new MovementComponent(this, settings.movementSettings)),
	marioState(MarioState::None)
{
	// Getting animations data
	animations = std::unordered_map<MarioState, std::vector<Animation>> {
		{MarioState::Small, Animations::Mario::Small::sMario},
		{MarioState::Large, Animations::Mario::Large::lMario},
		{MarioState::Fire, Animations::Mario::Large::fMario},
	};

	camera->SetBoundary(tilemap->GetTilemapBounds());
	UpdateState(MarioState::Small);
	UpdateAnimations();
}

Mario::~Mario()
{
	delete movementComponent;
}

void Mario::Update(const float deltaTime)
{
	Move(deltaTime);
	UpdateCameraFollow();

	UpdateAnimations();
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
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
	Rect playerBounds = collider->GetBoundsWithOffset(deltaVelocity);

	if (viewport.x > playerBounds.x)
	{
		velocity.x = 0.0f;
	}
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
	switch (movementComponent->GetState())
	{
	case MovementState::Standing:
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Standing]);
		break;
	case MovementState::Running:
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Walking]);
		break;
	case MovementState::TurningAround:
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::ChangeDir]);
		break;
	case MovementState::Jumping:
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Jumping]);
		break;
	}

	// There is a better way to do this most likely, but I don't want to think anymore
	// REFACTOR THIS LATER
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

void Mario::UpdateState(MarioState marioState)
{
	if (this->marioState == marioState) return;
	this->marioState = marioState;

	// Updating collider size
	switch (marioState)
	{
	case MarioState::Small:
		collider->SetSizeOffset(DirectX::XMFLOAT2(0.0f, -(sprite->GetSize().y / 2)));
		break;

	default:
		collider->SetSizeOffset(DirectX::XMFLOAT2(0.0f, 0.0f));
		break;
	}
}


