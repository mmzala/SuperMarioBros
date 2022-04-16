#pragma once

#include "../Settings/SpriteSettings.h"

class Transform;
class Sprite;
class RectBounds;

class GameObject
{
public:
	/// <summary>
	/// Creates an game object.
	/// </summary>
	/// <param name="spriteSettings">: Settings for the sprite </param>
	GameObject(SpriteSettings spriteSettings);
	virtual ~GameObject();

	virtual void Update(const float deltaTime);
	bool WasSeen();

public:
	Transform* transform;
	Sprite* sprite;
	RectBounds* bounds;

	/// <summary>
	/// Prevents the object from beeing updated.
	/// If the object is also a character, it prevents from checking collision with other characters
	/// </summary>
	bool isActive;

private:
	/// <summary>
	/// If the gameObject was seen on the screen
	/// </summary>
	bool wasSeen;
};

