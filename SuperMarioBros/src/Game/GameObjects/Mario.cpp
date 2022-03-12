#include "Mario.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Physics/RectCollider.h" // Collision
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h" // Camera follow
#include "../../Engine/Input/Input.h" // Checking input
#include "../World/Tilemap.h" // Tilemap for collision
#include "../../Engine/Physics/TilemapCollider.h" // Tilemap collision

Mario::Mario(SpriteSettings* spriteSettings, Tilemap* tilemap)
	:
	GameObject::GameObject(spriteSettings),
	tilemap(tilemap),
	tilemapCollider(new TilemapCollider(collider, tilemap)),
	camera(SMBEngine::GetInstance()->GetCamera()),
	marioState(MarioState::None)
{
	camera->SetBoundary(tilemap->GetTilemapBounds());
	sprite->SetFrame(0);
	UpdateMarioState(MarioState::Large);
}

Mario::~Mario()
{
	delete tilemapCollider;
}

void Mario::Update(const float deltaTime)
{
	DirectX::XMFLOAT2 velocity = DirectX::XMFLOAT2();
	Move(velocity, deltaTime);
	UpdateCameraFollow();

	sprite->Draw(transform->GetWorldMatrix());
}

void Mario::Move(DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	constexpr float gravity = 150.0f;
	constexpr float movementSpeed = 1000.0f;
	Input* input = Input::GetInstance();

	if (input->GetKey(DIK_W))
	{
		velocity.y += movementSpeed * deltaTime;
	}
	else
	{
		velocity.y -= gravity * deltaTime;
	}
	
	if (input->GetKey(DIK_A))  // Left movement
	{
		velocity.x += -movementSpeed * deltaTime;
		sprite->FlipSpriteX(true);
	}
	if (input->GetKey(DIK_D)) // Right movement
	{
		velocity.x += movementSpeed * deltaTime;
		sprite->FlipSpriteX(false);
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


