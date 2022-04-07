#pragma once

#include <DirectXMath.h> // XMFLOAT2
#include <functional>
#include <vector>

class Character;

/// <summary>
/// Handles collision with all the characters in the current gameplay scene
/// </summary>
class CharacterCollider
{
public:
	CharacterCollider(Character* character, std::function<void(Character* other)> callback);
	~CharacterCollider();

	void Update(const float deltaTime);

private:
	Character* character;
	std::function<void(Character* other)> callback;
	std::vector<Character*>& characters;
};

