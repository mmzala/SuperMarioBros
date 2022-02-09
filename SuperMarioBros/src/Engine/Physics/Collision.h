#pragma once

#include <Windows.h>

class Collision
{
public:
	/// <summary>
	/// Uses AABB collision detection to check if bounds are collided.
	/// WARNING, this doesn't work with rotations!
	/// </summary>
	/// <param name="bounds1"> First bounds </param>
	/// <param name="bounds2"> Seconds Bound </param>
	/// <returns> If bounds are collided </returns>
	static bool Check(RECT bounds1, RECT bounds2);
};

