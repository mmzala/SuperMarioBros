#include "Canvas.h"
#include "../../../Game/GameObjects/Components/Transform.h"
#include "UIElement.h"
#include "../../SMBEngine.h"
#include "../Camera.h"

Canvas::Canvas()
	:
	camera(SMBEngine::GetInstance()->GetCamera()),
	elements()
{}

Canvas::~Canvas()
{
	for (UIElement* element : elements)
	{
		delete element;
	}
	elements.clear();
}

void Canvas::Update()
{
	DirectX::XMFLOAT2 anchorCenter = camera->GetViewportCenter();

	for (UIElement* element : elements)
	{
		element->Draw(anchorCenter);
	}
}

void Canvas::AddElement(UIElement* element)
{
	elements.push_back(element);
}
