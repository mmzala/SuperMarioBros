#pragma once

#include "GameObject.h"
#include "../Settings/FlagSettings.h"

class Tilemap;

class Flag : public GameObject
{
public:
	Flag(FlagSettings settings, Tilemap* tilemap);
	~Flag() override;

	void Update(const float deltaTime) override;

private:
	DirectX::XMFLOAT2 topPosition;
	DirectX::XMFLOAT2 bottomPosition;
	float descendingSpeed;
};

