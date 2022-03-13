#pragma once

#include "../../Engine/Graphics/Animation.h"
#include <vector>

namespace Animations
{
	namespace Mario
	{
		// Enum's have no inheritance, so we are doing it this way :)
		struct AnimationState
		{
			static constexpr int Standing = 0;
			static constexpr int Walking = 1;
			static constexpr int ChangeDir = 2;
			static constexpr int Jumping = 3;
		};

		namespace Small
		{
			struct SAnimationState : AnimationState
			{
				static constexpr int GameOver = 4;
			};

			/// <summary>
			/// Small Mario animations
			/// </summary>
			static const std::vector<Animation> sMario = {
				Animation(21, 21, 0.0f), // Standing still
				Animation(22, 24, 10.0f), // Walking / Running
				Animation(25, 25, 0.0f), // Changing direction while walking / running
				Animation(26, 26, 0.0f), // Jumping
				Animation(27, 27, 0.0f), // Game over
			};
		}

		namespace Large
		{
			struct LAnimationState : AnimationState
			{
				static constexpr int Ducking = 4;
				static constexpr int GettingHit = 5;
			};

			/// <summary>
			/// Large Mario animations
			/// </summary>
			static const std::vector<Animation> lMario = {
				Animation(0, 0, 0.0f), // Standing still
				Animation(1, 3, 10.0f), // Walking / Running
				Animation(4, 4, 0.0f), // Changing direction while walking / running
				Animation(5, 5, 0.0f), // Jumping
				Animation(14, 14, 0.0f), // Ducking
				Animation(15, 15, 0.0f), // Getting Hit
			};

			/// <summary>
			/// Fire Mario animations
			/// </summary>
			static const std::vector<Animation> fMario = {
				Animation(35, 35, 0.0f), // Standing still
				Animation(36, 38, 10.0f), // Walking / Running
				Animation(39, 39, 0.0f), // Changing direction while walking / running
				Animation(40, 40, 0.0f), // Jumping
				Animation(49, 49, 0.0f), // Ducking
				Animation(50, 50, 0.0f), // Getting Hit
			};
		}
	}
}