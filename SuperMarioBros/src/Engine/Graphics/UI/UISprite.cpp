#include "UISprite.h"
#include "../../../Game/GameObjects/Components/Transform.h"
#include "../Animator.h"
#include "../../SMBEngine.h" // Getting deltaTime

UISprite::UISprite(UISpriteSettings settings)
	:
	Sprite::Sprite(settings),
	UIElement::UIElement(),
	animator(new Animator(this))
{
	animator->SetAnimation(settings.animation);
}

UISprite::~UISprite()
{
	delete animator;
}

void UISprite::Draw(const DirectX::XMFLOAT2& anchor)
{
	DirectX::XMFLOAT2 originalPosition = transform->position;
	transform->position.x += anchor.x;
	transform->position.y += anchor.y;

	animator->Update(SMBEngine::GetInstance()->GetDeltaTime());
	Sprite::Draw(transform->GetWorldMatrix());

	transform->position = originalPosition;
}
