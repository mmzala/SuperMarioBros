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

protected:
	Sprite* sprite;

public:
	RectCollider* collider; // Collider has to be here, because sprite needs to be initialized first to get the texture size
};

