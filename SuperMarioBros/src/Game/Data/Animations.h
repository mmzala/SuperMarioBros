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
			static constexpr int OnFlagPole = 4;
		};

		namespace Small
		{
			struct SAnimationState : AnimationState
			{
				static constexpr int GameOver = 5;
			};

			/// <summary>
			/// Small Mario animations
			/// </summary>
			static const std::vector<Animation> sMario = {
				Animation(21, 21, 0.0f), // Standing still
				Animation(22, 24, 10.0f), // Walking / Running
				Animation(25, 25, 0.0f), // Changing direction while walking / running
				Animation(26, 26, 0.0f), // Jumping
				Animation(28, 29, 5.0f), // On flag pole
				Animation(27, 27, 0.0f), // Game over
			};
		}

		namespace Large
		{
			struct LAnimationState : AnimationState
			{
				static constexpr int Ducking = 5;
				static constexpr int Transitional = 6;
			};

			/// <summary>
			/// Large Mario animations
			/// </summary>
			static const std::vector<Animation> lMario = {
				Animation(0, 0, 0.0f), // Standing still
				Animation(1, 3, 10.0f), // Walking / Running
				Animation(4, 4, 0.0f), // Changing direction while walking / running
				Animation(5, 5, 0.0f), // Jumping
				Animation(6, 7, 5.0f), // On flag pole
				Animation(14, 14, 0.0f), // Ducking
				Animation(15, 15, 5.0f), // Transitional
			};

			struct FAnimationState : LAnimationState
			{
				static constexpr int ThorwingFireBallStanding = 7;
				static constexpr int ThorwingFireBallRunning = 8;
				static constexpr int ThorwingFireBallJump = 9;
			};

			/// <summary>
			/// Fire Mario animations
			/// </summary>
			static const std::vector<Animation> fMario = {
				Animation(35, 35, 0.0f), // Standing still
				Animation(36, 38, 10.0f), // Walking / Running
				Animation(39, 39, 0.0f), // Changing direction while walking / running
				Animation(40, 40, 0.0f), // Jumping
				Animation(41, 42, 5.0f), // On flag pole
				Animation(49, 49, 0.0f), // Ducking
				Animation(50, 50, 5.0f), // Transitional
				Animation(51, 51, 0.0f), // Throwing fire ball while standing
				Animation(51, 53, 10.0f), // Throwing fire ball while running
				Animation(55, 55, 0.0f), // Throwing fire ball while jumping
			};
		}
	}

	namespace Goomba
	{
		// Enum's have no inheritance, so we are doing it this way :)
		struct AnimationState
		{
			static constexpr int Walking = 0;
			static constexpr int Dead = 1;
		};

		/// <summary>
		/// Goomba animations
		/// </summary>
		static const std::vector<Animation> goomba = {
			Animation(0, 1, 5.0f), // Walking / Running
			Animation(2, 2, 0.0f), // Dead
		};
	}
}