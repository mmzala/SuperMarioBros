#include "Flag.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../World/Tilemap/Tilemap.h"

Flag::Flag(FlagSettings settings, Tilemap* tilemap)
	:
	GameObject::GameObject(settings.spriteSettings),
	topPosition(tilemap->GetPositionInWorldCoordinates(settings.poleTopPosition)),
	bottomPosition(tilemap->GetPositionInWorldCoordinates(settings.poleBottomPosition)),
	descendingSpeed(settings.descendingSpeed),
	interpolationValue(0.0f),
	moveDownwards(false)
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

	// Move to the bottom of the pole when needed
	if (moveDownwards && interpolationValue <= 1.0f)
	{
		transform->position.y = Math::Lerp(topPosition.y, bottomPosition.y, interpolationValue);
		interpolationValue += descendingSpeed * deltaTime;
	}
}


