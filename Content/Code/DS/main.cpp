#include <iostream>
#include <vector>
#include "Stack.h"

using namespace std;
using namespace dsc;

int binarySearch(const vector<int>& arr, int target)
{
    int left = 0;
    int right = arr.size() -1;
    int count = 0;

    while (left <= right)
    {
        count++;
        // int middle = (left + right) / 2;
        int middle = left + (right - left) / 2;
        
        if (arr[middle] == target)
        {
            cout << "Count: " << count << endl;
            return middle;
        }
        if (arr[middle] < target)
        {
            left = middle + 1;
        }
        else // if (arr[middle] > target)
        {
            right = middle - 1;
        }
    }
    cout << "Count: " << count << endl;
    return -1;
}

int main()
{
    vector<int> arr;

    for (int i = 0; i < 1000000; ++i)
    {
        arr.push_back(i * 2 + 3);
    }

    int index = binarySearch(arr, 457);
    cout << "Found at index " << index << ".\n";

    cout << static_cast<size_t>(-1) << endl;
    return 0;
}