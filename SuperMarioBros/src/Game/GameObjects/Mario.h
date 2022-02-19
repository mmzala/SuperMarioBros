#pragma once
#include "GameObject.h"

class Mario : public GameObject
{
public:
	Mario(SpriteSettings* spriteSettings);
	~Mario();

	void Update(float deltaTime) override;
};

