#pragma once

class Math
{
public:
	static float Lerp(const float a, const float b, const float f)
	{
		return a + f * (b - a);
	}

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
};