#pragma once

class Transform;
class Sprite;
class RectCollider;

class GameObject
{
public:
	GameObject(const char* textureFile);
	~GameObject();

	void Update(float deltaTime);

public:
	Transform* transform;

private:
	Sprite* sprite;

public:
	RectCollider* collider; // Collider has to be here, because sprite needs to be initialized first to get the texture size
};

