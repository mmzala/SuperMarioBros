#pragma once

#include "../../Engine/Graphics/UI/Text.h"
#include "../../Utils/PoolableObject.h"

/// <summary>
/// Text used for when the player gains points
/// </summary>
class ScoringText : public Text, public PoolableObject
{
public:
	ScoringText(TextSettings settings);
	void Draw(const DirectX::XMFLOAT2& anchor) override;
	void SetInUse(bool value) override;

private:
	float speed;
	float aliveTime;
};

