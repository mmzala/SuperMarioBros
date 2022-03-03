#pragma once

#include <Windows.h> // RECT and DEFINE_ENUM_FLAG_OPERATORS

enum class CheckSide
{
	None = 0,
	Top = 1,
	Bottom = 2,
	Right = 4,
	Left = 8,
};
DEFINE_ENUM_FLAG_OPERATORS(CheckSide);

class Collision
{
public:
	/// <summary>
	/// Uses AABB collision detection to check if bounds are collided.
	/// WARNING, this doesn't work with rotations!
	/// </summary>
	/// <param name="bounds1">: First bounds </param>
	/// <param name="bounds2">: Seconds Bound </param>
	/// <returns> If bounds are collided </returns>
	static bool RectCheck(RECT bounds1, RECT bounds2);

	/// <summary>
	/// Checks collision between tile and collider
	/// </summary>
	/// <param name="tileBounds">: Bounds of the tile </param>
	/// <param name="bounds">: Bounds of the collider </param>
	/// <param name="side">: At what side the collision happened </param>
	/// <returns> If the bounds are overlapping with the tile and what side it was </returns>
	static bool TileCheck(RECT tileBounds, RECT bounds, CheckSide& side);
};

