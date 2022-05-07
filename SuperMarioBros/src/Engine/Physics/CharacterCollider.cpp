#include "CharacterCollider.h"
#include "../../Utils/Math.h" // * operator overload
#include "RectBounds.h"
#include "../../Game/GameObjects/Character.h"
#include "Collision.h"

// Getting character vector from current scene
#include "../../Engine/SMBEngine.h"
#include "../../Game/Game.h"
#include "../../Game/World/Scenes/GameplayScene.h"

CharacterCollider::CharacterCollider(Character* character, std::function<void(Character* other)> callback)
	:
	ignoreCollision(false),
	character(character),
	callback(callback),
	// CharacterCollider is only used in gameplay scenes, so we can always be sure that we can cast to GameplayScene* safely
	characters(static_cast<GameplayScene*>(SMBEngine::GetInstance()->GetGame()->GetCurrentScene())->GetCharacters()),
	ignoreCharacters()
{}

CharacterCollider::~CharacterCollider()
{}

void CharacterCollider::Update(const float deltaTime)
{
	if (ignoreCollision) return;

	Rect bounds = character->bounds->GetBoundsWithPositionOffset(character->GetVelocity() * deltaTime);

	for (Character* character : characters)
	{
		if (character->characterCollider->ignoreCollision ||
			this->character == character ||
			!character->isActive ||
			std::find(ignoreCharacters.begin(), ignoreCharacters.end(), typeid(*character).name()) != ignoreCharacters.end())
		{
			continue;
		}
		
		if (Collision::RectCheck(bounds, character->bounds->GetBounds()))
		{
			callback(character);
		}
	}
}
