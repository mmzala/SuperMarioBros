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

	template<class T>
	void AddCharacterTypeToIgnore();

	template<class T>
	void RemoveCharacterTypeToIgnore();

private:
	Character* character;
	std::function<void(Character* other)> callback;
	std::vector<Character*>& characters;
	std::vector<const char*> ignoreCharacters;
};

template<class T>
inline void CharacterCollider::AddCharacterTypeToIgnore()
{
	// Returns if type is already being ignored
	const char* name = typeid(T).name();
	if (std::find(ignoreCharacters.begin(), ignoreCharacters.end(), name) != ignoreCharacters.end()) return;
	ignoreCharacters.push_back(name);
}

template<class T>
inline void CharacterCollider::RemoveCharacterTypeToIgnore()
{
	ignoreCharacters.erase(std::remove(ignoreCharacters.begin(), ignoreCharacters.end(), typeid(T).name()), ignoreCharacters.end());
}
