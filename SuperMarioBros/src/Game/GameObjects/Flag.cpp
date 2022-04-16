#include "Flag.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../World/Tilemap/Tilemap.h"

Flag::Flag(FlagSettings settings, Tilemap* tilemap)
	:
	GameObject::GameObject(settings.spriteSettings),
	topPosition(tilemap->GetPositionInWorldCoordinates(settings.poleTopPosition)),
	bottomPosition(tilemap->GetPositionInWorldCoordinates(settings.poleBottomPosition)),
	descendingSpeed(settings.descendingSpeed)
{
	// Position flag correctly on the X axis on the pole
	DirectX::XMFLOAT2 position = DirectX::XMFLOAT2(topPosition.x - sprite->GetSize().x * transform->scale.x, topPosition.y);
	transform->position = position;
}

Flag::~Flag()
{}

void Flag::Update(const float deltaTime)
{
	if (!WasSeen()) return;
	GameObject::Update(deltaTime);
}


