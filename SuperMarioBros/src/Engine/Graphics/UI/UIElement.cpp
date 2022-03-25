#include "UIElement.h"
#include "../../../Game/GameObjects/Components/Transform.h"

UIElement::UIElement()
	:
	transform(new Transform())
{}

UIElement::~UIElement()
{
	delete transform;
}

void UIElement::Draw(DirectX::XMFLOAT2 anchor)
{}
