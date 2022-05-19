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

void UIElement::Draw(const DirectX::XMFLOAT2& anchor)
{}
