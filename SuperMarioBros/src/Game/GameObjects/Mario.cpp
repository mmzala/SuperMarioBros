#include "Mario.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Graphics/Animator.h"
#include "../../Engine/Physics/RectCollider.h" // Collision
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h" // Camera follow
#include "../../Engine/Input/Input.h" // Checking input
#include "../World/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision
#include "../Data/Animations.h" // Animations data

Mario::Mario(SpriteSettings* spriteSettings, Tilemap* tilemap)
	:
	GameObject::GameObject(spriteSettings),
	animator(new Animator(sprite)),
	tilemap(tilemap),
	tilemapCollider(new TilemapCollider(collider, tilemap)),
	camera(SMBEngine::GetInstance()->GetCamera()),
	marioState(MarioState::None)
{
	// Getting animations data
	animations = std::unordered_map<MarioState, std::vector<Animation>> {
		{MarioState::Small, Animations::Mario::Small::sMario},
		{MarioState::Large, Animations::Mario::Large::lMario},
		{MarioState::Fire, Animations::Mario::Large::fMario},
	};

	camera->SetBoundary(tilemap->GetTilemapBounds());
	sprite->SetFrame(0);

	UpdateMarioState(MarioState::Large);
}

Mario::~Mario()
{
	delete animator;
	delete tilemapCollider;
}

void Mario::Update(const float deltaTime)
{
	DirectX::XMFLOAT2 velocity = DirectX::XMFLOAT2();
	Move(velocity, deltaTime);
	UpdateCameraFollow();

	animator->Update(deltaTime);
	sprite->Draw(transform->GetWorldMatrix());
}

void Mario::Move(DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	constexpr float gravity = 150.0f;
	constexpr float movementSpeed = 500.0f;
	Input* input = Input::GetInstance();

	bool up = input->GetKey(DIK_W);
	if (up)
	{
		velocity.y += movementSpeed / 2 * deltaTime;
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Jumping]);
	}
	else
	{
		velocity.y -= gravity * deltaTime;
	}
	
	bool left = input->GetKey(DIK_A);
	bool right = input->GetKey(DIK_D);
	if (left)  // Left movement
	{
		velocity.x += -movementSpeed * deltaTime;
		sprite->FlipSpriteX(true);
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Walking]);
	}
	if (right) // Right movement
	{
		velocity.x += movementSpeed * deltaTime;
		sprite->FlipSpriteX(false);
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Walking]);
	}

	if (!left && !right && !up)
	{
		animator->SetAnimation(animations[marioState][Animations::Mario::AnimationState::Standing]);
	}

	CheckCollision(velocity);
	transform->position = DirectX::XMFLOAT2(transform->position.x + velocity.x, transform->position.y + velocity.y);
}

void Mario::CheckCollision(DirectX::XMFLOAT2& velocity)
{
	tilemapCollider->Update(velocity);

	// Making sure the player cannot go back
	Rect viewport = camera->GetViewportBounds();
	Rect playerBounds = collider->GetBoundsWithOffset(velocity);

	if (viewport.x >= playerBounds.x)
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
	// camera->FollowPosition(transform->position, true, false);
}

void Mario::UpdateMarioState(MarioState marioState)
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


