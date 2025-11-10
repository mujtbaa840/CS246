#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Map.h"

using namespace std;
using namespace dsc;

template <typename K, typename V>
// using Map = MapOpen<K, V>;
using Map = MapChain<K, V>;

bool testMap()
{
    Map<int, string> map;
    map.put(1, "one");
    map.put(2, "two");
    map.put(3, "three");

    cout << "Map contents: " << map << endl;

    cout << "Key 2 maps to value: " << map.get(2) << endl;

    map.remove(2);
    cout << "After removing key 2, map contents: " << map << endl;

    try
    {
        map.get(2);
    }
    catch (const out_of_range& e)
    {
        cout << "Caught exception as expected when accessing removed key 2: " << e.what() << endl;
    }

    return true;
}

vector<int> twoSum(const vector<int>& nums, int target)
{
    Map<int, int> map;
    for (int i = 0; i < nums.size(); i++)
    {
        if (map.contains(target - nums[i]))
        {
            return {map.get(target - nums[i]), i};
        }
        map.put(nums[i], i);
    }
    return {};
}

// int fibonacci(int n, Map<int, int> memo)
// {

// }



int main()
{
    // testMap();

    vector<int> nums = {10, 5, 3, 7};
    int target = 14;

    vector<int> result = twoSum(nums, target);

    cout << result.size() << endl;
    
    return 0;
}