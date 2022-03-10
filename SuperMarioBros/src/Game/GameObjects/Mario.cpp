#include "Mario.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Physics/RectCollider.h"
#include "../../Engine/SMBEngine.h" // Getting camera
#include "../../Engine/Graphics/Camera.h" // Camera follow
#include "../../Engine/Input/Input.h" // Checking input
#include "../World/Tilemap.h" // Getting tiles for collision
#include <cmath> // floor and ceil

Mario::Mario(SpriteSettings* spriteSettings, Tilemap* tilemap)
	:
	GameObject::GameObject(spriteSettings),
	tilemap(tilemap),
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
	Rect bounds = collider->GetBounds();
	Rect vBounds = collider->GetBoundsWithOffset(velocity);

	// Bottom left collision
	DirectX::XMFLOAT2 checkPosition = DirectX::XMFLOAT2(bounds.x, vBounds.y);
	DirectX::XMFLOAT2 tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Bottom))
	{
		velocity.y = 0.0f;
	}

	// Bottom right collision
	checkPosition = DirectX::XMFLOAT2(bounds.x + bounds.width, vBounds.y);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Bottom))
	{
		velocity.y = 0.0f;
	}

	// Top left collision
	checkPosition = DirectX::XMFLOAT2(bounds.x, vBounds.y + vBounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Top))
	{
		velocity.y = 0.0f;
	}

	// Top right collision
	checkPosition = DirectX::XMFLOAT2(bounds.x + bounds.width, vBounds.y + vBounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Top))
	{
		velocity.y = 0.0f;
	}

	// Left bottom collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x, bounds.y);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Left))
	{
		velocity.x = 0.0f;
	}

	// Left top collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x, bounds.y + bounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Left))
	{
		velocity.x = 0.0f;
	}

	// Right bottom collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x + vBounds.width, bounds.y);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Right))
	{
		velocity.x = 0.0f;
	}

	// Right top collision
	checkPosition = DirectX::XMFLOAT2(vBounds.x + vBounds.width, bounds.y + bounds.height);
	tilemapPosition = tilemap->GetPositionInTilemapCoordinates(checkPosition);
	if (CheckTileCollision(vBounds, tilemapPosition, CheckSide::Right))
	{
		velocity.x = 0.0f;
	}
}

bool Mario::CheckTileCollision(Rect bounds, DirectX::XMFLOAT2 fTilemapPosition, CheckSide side)
{
	DirectX::XMINT2 tilemapPosition = DirectX::XMINT2((int32_t)std::round(fTilemapPosition.x), (int32_t)std::round(fTilemapPosition.y));
	if (!tilemap->CheckCollisionTile(tilemapPosition)) return false;
	return Collision::TilemapCheck(tilemap->GetTileBounds(tilemapPosition), bounds, side);
}

void Mario::UpdateCameraFollow()
{
	DirectX::XMFLOAT2 viewportCenter = camera->GetViewportCenter();

	if (viewportCenter.x < transform->position.x)
	{
		camera->FollowPosition(transform->position, true, false);
	}
}
