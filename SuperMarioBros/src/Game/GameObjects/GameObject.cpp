#include "GameObject.h"
#include "../../Engine/Graphics/Sprite.h"

GameObject::GameObject(const char* textureFile)
	:
	position(DirectX::XMFLOAT2(0.0f, 0.0f)),
	rotation(0.0f),
	scale(DirectX::XMFLOAT2(1.0f, 1.0f)),
	sprite(new Sprite(textureFile))
{}

GameObject::~GameObject()
{
	delete sprite;
}

void GameObject::Update(float deltaTime)
{
	sprite->Draw(GetWorldMatrix());
}

DirectX::XMMATRIX GameObject::GetWorldMatrix()
{
	using namespace DirectX;

	XMMATRIX translation = XMMatrixTranslation(position.x, position.y, 0.0f);
	XMMATRIX rotation = XMMatrixRotationZ(this->rotation);
	XMMATRIX scale = XMMatrixScaling(this->scale.x, this->scale.y, 1.0f);

	return scale * rotation * translation;
}

void GameObject::SetPosition(DirectX::XMFLOAT2 position)
{
	this->position = position;
}

void GameObject::SetRotation(float rotation)
{
	this->rotation = rotation;
}

void GameObject::SetScale(DirectX::XMFLOAT2 scale)
{
	this->scale = scale;
}
