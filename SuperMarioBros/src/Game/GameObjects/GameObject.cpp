#include "GameObject.h"
#include "Components/Transform.h"
#include "../../Engine/Graphics/Sprite.h"
#include "../../Engine/Physics/RectBounds.h"
#include "../../Engine/SMBEngine.h"
#include "../../Engine/Graphics/Camera.h"
#include "../../Engine/Physics/Collision.h"

GameObject::GameObject(SpriteSettings spriteSettings)
	:
	transform(new Transform()),
	sprite(new Sprite(SpriteSettings(spriteSettings.textureFile, spriteSettings.spriteSheetSize))),
	bounds(new RectBounds(sprite->GetSize(), transform))
{
	sprite->SetFrame(0);
}

GameObject::~GameObject()
{
	delete bounds;
	delete sprite;
	delete transform;
}

void GameObject::Update(const float deltaTime)
{
	sprite->Draw(transform->GetWorldMatrix());
}

bool GameObject::IsInViewingFrustum()
{
	Rect viewingFrustum = SMBEngine::GetInstance()->GetCamera()->GetViewportBounds();
	return Collision::RectCheck(bounds->GetBounds(), viewingFrustum);
}
