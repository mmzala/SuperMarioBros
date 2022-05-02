#pragma once

#include "CharacterSettings.h"

struct EnemySettings : public CharacterSettings
{
	float timeAfterDeath;

	EnemySettings(float timeAfterDeath = 0.0f)
		:
		CharacterSettings::CharacterSettings(),
		timeAfterDeath(timeAfterDeath)
	{}
};