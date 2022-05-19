#include "ScoringText.h"
#include "../GameObjects/Components/Transform.h"
#include "../../Engine/SMBEngine.h"

ScoringText::ScoringText(TextSettings settings)
	:
	Text::Text(settings),
	speed(100.0f),
	aliveTime(0.8f)
{}

void ScoringText::Draw(const DirectX::XMFLOAT2& anchor)
{
	float deltaTime = SMBEngine::GetInstance()->GetDeltaTime();
	transform->position.y += speed * deltaTime;
	Text::Draw(anchor);

	aliveTime -= deltaTime;
	if (aliveTime < 0.0f)
	{
		SetInUse(false);
	}
}

void ScoringText::SetInUse(bool value)
{
	PoolableObject::SetInUse(value);
	aliveTime = 0.8f;
}
