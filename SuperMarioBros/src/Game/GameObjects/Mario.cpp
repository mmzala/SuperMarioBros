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
#include <algorithm> // fmax / fmin
#include "../../Utils/Debug.h" // Debugging

Mario::Mario(MarioSettings settings)
	:
	Character::Character(CharacterSettings(settings.spriteSettings, settings.tilemap, settings.walkingSpeed, settings.gravity)),
	camera(SMBEngine::GetInstance()->GetCamera()),
	marioState(MarioState::None),
	runningSpeed(settings.runningSpeed),
	walkingAcceleration(settings.walkingAcceleration),
	runningAcceleration(settings.runningAcceleration),
	releaseDeceleration(settings.releaseDeceleration),
	skiddingDeceleration(settings.skiddingDeceleration),
	skidTurnaroundSpeed(settings.skidTurnaroundSpeed),
	runningDecelerationDelay(settings.runningDecelerationDelay),
	runningDecelerationTimer(0.0f)
{
	// Getting animations data
	animations = std::unordered_map<MarioState, std::vector<Animation>> {
		{MarioState::Small, Animations::Mario::Small::sMario},
		{MarioState::Large, Animations::Mario::Large::lMario},
		{MarioState::Fire, Animations::Mario::Large::fMario},
	};

	camera->SetBoundary(tilemap->GetTilemapBounds());
	UpdateState(MarioState::Small);
}

Mario::~Mario()
{}

void Mario::Update(const float deltaTime)
{
	Move(deltaTime);
	UpdateCameraFollow();
	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Mario::Move(const float deltaTime)
{
	Input* input = Input::GetInstance();
	velocity.y = -gravity;
	
	const bool leftInput = input->GetKey(DIK_LEFTARROW) || input->GetKey(DIK_A);
	const bool rightInput = input->GetKey(DIK_RIGHTARROW) || input->GetKey(DIK_D);
	const bool runInput = input->GetKey(DIK_Z);
	MoveHorizontal(leftInput, rightInput, runInput, deltaTime);

	Character::Move(deltaTime);
}

void Mario::MoveHorizontal(const bool leftInput, const bool rightInput, const bool runInput, const float deltaTime)
{
	// If you stop holding "run" input, but continue running in the same direction, Mario will
	// , keep moving at current speed (runningSpeed) for runningDecelerationDelay amount.
	// That's why you don't lose any speed when firing fireballs while running.
	bool shouldRun = false;
	if (runInput) runningDecelerationTimer = runningDecelerationDelay;
	else
	{
		if (std::abs(velocity.x) > walkingSpeed)
		{
			runningDecelerationTimer -= deltaTime;

			if (runningDecelerationTimer > 0.0f) shouldRun = true;
		}
	}

	float movementSpeed = runInput || shouldRun ? runningSpeed : walkingSpeed;
	float movementAccelertion = runInput ? runningAcceleration : walkingAcceleration;

	if (leftInput && !rightInput)  // Left movement
	{
		// If velocity is too high then go back to the max velocity slowly
		if (-movementSpeed > velocity.x)
		{
			velocity.x = velocity.x + releaseDeceleration;
		}
		else
		{
			if (velocity.x > 0.0f)
			{
				velocity.x = velocity.x - skidTurnaroundSpeed;
			}
			else
			{
				velocity.x = std::fmax(velocity.x - movementAccelertion, -movementSpeed);
			}
		}
		
		sprite->FlipSpriteX(true);
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Walking]);
	}

	if (rightInput && !leftInput) // Right movement
	{
		if (movementSpeed < velocity.x)
		{
			velocity.x = velocity.x - releaseDeceleration;
		}
		else
		{
			if (velocity.x < 0.0f)
			{
				velocity.x = velocity.x + skidTurnaroundSpeed;
			}
			else 
			{
				velocity.x = std::fmin(velocity.x + movementAccelertion, movementSpeed);
			}
		}
		
		sprite->FlipSpriteX(false);
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Walking]);
	}

	if (!leftInput && !rightInput || leftInput && rightInput) // No input
	{
		if (velocity.x < 0)
		{
			velocity.x = std::fmin(0.0f, velocity.x + skiddingDeceleration);
		}
		else if (velocity.x > 0)
		{
			velocity.x = std::fmax(0.0f, velocity.x - skiddingDeceleration);
		}

		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Standing]);
	}

	Debug::Log("Velocity X: %f\n", velocity.x, velocity.y);
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


