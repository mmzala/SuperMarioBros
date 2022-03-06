#pragma once

#include "Rect.h"
#include <Windows.h> // DEFINE_ENUM_FLAG_OPERATORS

enum class CheckSide
{
	Top = 1 << 0,
	Bottom = 1 << 1,
	Right = 1 << 2,
	Left = 1 << 3,
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
	static bool RectCheck(Rect bounds1, Rect bounds2);

	/// <summary>
	/// Checks collision between a tile and a character collider.
	/// </summary>
	/// <param name="tileBounds">: Bounds of the tile</param>
	/// <param name="characterBounds">: Bounds of the character </param>
	/// <param name="side">: What side to check the collision on </param>
	/// <returns> If tile and character collided on the given CheckSide </returns>
	static bool TilemapCheck(Rect tileBounds, Rect characterBounds, CheckSide side);

private:
	static bool BottomTileCheck(Rect tileBounds, Rect characterBounds);
	static bool TopTileCheck(Rect tileBounds, Rect characterBounds);
	static bool LeftTileCheck(Rect tileBounds, Rect characterBounds);
	static bool RightTileCheck(Rect tileBounds, Rect characterBounds);
	
};

