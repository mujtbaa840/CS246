#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
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

bool testMap2()
{
    Map<string, int> map;
    map["apple"] = 1;
    map["banana"] = 2;
    map["cherry"] = 3;

    cout << "Map contents: " << map << endl;

    cout << "Key 'banana' maps to value: " << map["banana"] << endl;

    map.remove("banana");
    cout << "After removing key 'banana', map contents: " << map << endl;

    try
    {
        cout << map.get("banana") << endl;
    }
    catch (const out_of_range& e)
    {
        cout << "Caught exception as expected when accessing removed key 'banana': " << e.what() << endl;
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
            return {map[target - nums[i]], i};
        }
        map[nums[i]] = i;
    }
    return {};
}

// int fibonacci(int n, Map<int, int>& memo)
// {

// }



int main()
{
    // testMap();
    // cout << endl;
    // testMap2();
    // cout << endl;

    // vector<int> nums = {10, 5, 3, 7};
    // int target = 11;

    // vector<int> result = twoSum(nums, target);

    
    // if (result.size() > 0)
    // {
    //     cout << "{" << result[0] << ", " << result[1] << "}" << endl;
    // }
    // else
    // {
    //     cout << "{}" << endl;
    // }

    Map<string, string> phonebook;

    phonebook.put("Arnold", "123-456-7890");
    phonebook["Beverly"] = "987-654-3210";

    cout << phonebook["Beverly"] << endl;
    cout << phonebook.get("Arnold") << endl;
    
    unordered_map<int, int> myMap;
    using Map1 = unordered_map<int,int>;


    return 0;
}