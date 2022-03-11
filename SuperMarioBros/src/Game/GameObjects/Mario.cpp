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
	camera(SMBEngine::GetInstance()->GetCamera())
{
	camera->SetBoundary(tilemap->GetTilemapBounds());
	sprite->SetFrame(24);
}

Mario::~Mario()
{}

void Mario::Update(const float deltaTime)
{
	DirectX::XMFLOAT2 velocity = DirectX::XMFLOAT2();
	Move(velocity, deltaTime);
	UpdateCameraFollow();

	sprite->Draw(transform->GetWorldMatrix());
}

void Mario::Move(DirectX::XMFLOAT2& velocity, const float deltaTime)
{
	constexpr float gravity = 100.0f;
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
	
	velocity.x += input->GetKey(DIK_A) * -movementSpeed * deltaTime; // Left movement
	velocity.x += input->GetKey(DIK_D) * movementSpeed * deltaTime; // Right movement

	CheckCollision(velocity);
	transform->position = DirectX::XMFLOAT2(transform->position.x + velocity.x, transform->position.y + velocity.y);
}

void Mario::CheckCollision(DirectX::XMFLOAT2& velocity)
{
	tilemapCollider->Update(velocity);
}

void Mario::UpdateCameraFollow()
{
	DirectX::XMFLOAT2 viewportCenter = camera->GetViewportCenter();

	if (viewportCenter.x < transform->position.x)
	{
		camera->FollowPosition(transform->position, true, false);
	}
}
