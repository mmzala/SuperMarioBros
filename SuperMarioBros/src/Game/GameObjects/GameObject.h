#pragma once

class Transform;
class Sprite;
struct SpriteSettings;
class RectCollider;

class GameObject
{
public:
	/// <summary>
	/// Creates an game object.
	/// DELETE spriteSettings after passing it here
	/// </summary>
	/// <param name="spriteSettings">: Sprite settings, DELETE THIS AFTER USING IT!!! </param>
	GameObject(SpriteSettings* spriteSettings);
	virtual ~GameObject();

	virtual void Update(const float deltaTime);

public:
	Transform* transform;

protected:
	Sprite* sprite;

public:
	RectCollider* collider; // Collider has to be here, because sprite needs to be initialized first to get the texture size
};

