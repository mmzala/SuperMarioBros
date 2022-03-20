#pragma once

#include <DirectXMath.h>

namespace DirectX
{
    inline bool operator==(const DirectX::XMINT2& first, const DirectX::XMINT2& second)
    {
        if (first.x == second.x &&
            first.y == second.y)
        {
            return true;
        }
        return false;
    }
}

class Math
{
public:
	static float Lerp(const float a, const float b, const float f)
	{
		return a + f * (b - a);
	}

	/// <summary>
	/// Finds closest integer value in the array
	/// </summary>
	/// <param name="array">: Array to search in </param>
	/// <param name="arrayayLength">: Lenght of the array </param>
	/// <param name="target">: What to search for </param>
	/// <returns> Closest value to the target in the array </returns>
	static int FindClosest(const int* array, const int arrayayLength, const int target)
	{
        // Corner cases
        if (target <= array[0])
            return array[0];
        if (target >= array[arrayayLength - 1])
            return array[arrayayLength - 1];

        // Doing binary search
        int i = 0, j = arrayayLength, mid = 0;
        while (i < j) {
            mid = (i + j) / 2;

            if (array[mid] == target)
                return array[mid];

            // If target is less than arrayay element,
            // then search in left
            if (target < array[mid]) {

                // If target is greater than previous
                // to mid, return closest of two
                if (mid > 0 && target > array[mid - 1])
                    return GetClosest(array[mid - 1],
                        array[mid], target);

                // Repeat for left half
                j = mid;
            }

            // If target is greater than mid
            else {
                if (mid < arrayayLength - 1 && target < array[mid + 1])
                    return GetClosest(array[mid],
                        array[mid + 1], target);
                // update i
                i = mid + 1;
            }
        }

        // Only single element left after search
        return array[mid];
	}

    static int GetClosest(int value1, int value2, int target)
    {
        if (target - value1 >= value2 - target)
        {
            return value2;
        }
        else
        {
            return value1;
        }
    }

    /// <summary>
    /// Finds the index of an element in a vector
    /// </summary>
    /// <typeparam name="T">: Any object that can compare each other </typeparam>
    /// <param name="vector">: Vector of objects to compare </param>
    /// <param name="element">: What element to find </param>
    /// <returns> If an element exists in a vector and its index </returns>
    template <typename T>
    static std::pair<bool, int> FindInVector(const std::vector<T>& vector, const T& element)
    {
        std::pair<bool, int> result;

        auto find = std::find(vector.begin(), vector.end(), element);
        if (find != vector.end())
        {
            result.first = true;
            result.second = distance(vector.begin(), find);
        }
        else
        {
            result.first = false;
            result.second = -1;
        }

        return result;
    }
};