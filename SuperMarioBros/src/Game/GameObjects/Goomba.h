#pragma once

#include "Enemy.h"
#include "../../Engine/Graphics/Animation.h" // Animation vector
#include <vector> // Animation vector

class Goomba : public Enemy
{
public:
	Goomba(EnemySettings settings);
	~Goomba() override;

	void Update(const float deltaTime) override;
	void OnHeadStomp() override;

protected:
	void UpdateState(EnemyState state) override;

private:
	std::vector<Animation> animations;
};

