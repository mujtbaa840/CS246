#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <vector>
#include <string>

namespace dsc
{
    template <typename T>
    unsigned int binarySearch(const std::vector<T>& arr, const T& target)
    {
        size_t left = 0;
        size_t right = arr.size() - 1;

        while (left <= right)
        {
            size_t mid = left + (right - left) / 2;

            if (arr[mid] == target)
            {
                return mid;
            }
            else if (arr[mid] < target)
            {
                left = mid + 1;
            }
            else // if (arr[mid] > target)
            {
                right = mid - 1;
            }
        }
        return arr.size(); // Target not found
    }
}
#endif