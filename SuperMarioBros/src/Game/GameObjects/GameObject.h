#pragma once

#include "../Settings/SpriteSettings.h"

class Transform;
class Sprite;
class RectCollider;

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
	bool IsInViewingFrustum();

public:
	Transform* transform;
	Sprite* sprite;
	RectCollider* collider;
};

