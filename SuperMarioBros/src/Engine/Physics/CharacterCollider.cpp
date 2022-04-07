#include "CharacterCollider.h"
#include "RectBounds.h"
#include "../../Game/GameObjects/Character.h"
#include "Collision.h"
#include "../../Engine/SMBEngine.h"
#include "../../Game/Game.h"
#include "../../Game/World/Scenes/GameplayScene.h"
#include "../../Utils/Math.h" // * operator overload

CharacterCollider::CharacterCollider(Character* character, std::function<void(Character* other)> callback)
	:
	character(character),
	callback(callback),
	// CharacterCollider is only used in gameplay scenes, so we can always be sure that we can cast to GameplayScene* safely
	characters(static_cast<GameplayScene*>(SMBEngine::GetInstance()->GetGame()->GetCurrentScene())->GetCharacters())
{}

CharacterCollider::~CharacterCollider()
{}

void CharacterCollider::Update(const float deltaTime)
{
	Rect bounds = character->bounds->GetBoundsWithOffset(character->GetVelocity() * deltaTime);

	for (Character* character : characters)
	{
		if (this->character == character || !character->isActive) continue;

		if (Collision::RectCheck(bounds, character->bounds->GetBounds()))
		{
			callback(character);
		}
	}
}
