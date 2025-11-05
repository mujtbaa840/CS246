#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Set.h"


using namespace std;
using namespace dsc;

template <typename T>
using Set = SetOpen<T>;
// using Set = SetChain<T>;

template <typename T>
bool anyDuplicates(const vector<T>& arr)
{
    Set<T> set;
    // for (auto v : arr)
    // {
    //     set.insert(v);
    // }
    // return set.size() < arr.size();

    for (auto v : arr)
    {
        if (set.contains(v))
        {
            return true;
        }
        set.insert(v);
    }
    return false;
}

bool uniqueString(const string& str)
{
    Set<char> set;
    for (char c : str)
    {
        if (set.contains(c))
        {
            return false;
        }
        set.insert(c);
    }
    return true;
}   

bool twoSum(const vector<int>& arr, int target)
{
    Set<int> set;
    for (int num : arr)
    {
        if (set.contains(target - num))
        {
            return true;
        }
        set.insert(num);
    }
    return false;
}

bool isAnagram(const string& str1, const string& str2)
{
    if (str1.length() != str2.length())
    {
        return false;
    }
    Set<char> set;
    for (char c : str1)
    {
        set.insert(c);
    }
    for (char c : str2)
    {
        if (!set.contains(c))
        {
            return false;
        }
        set.remove(c);
    }
    return set.size() == 0;
}

int main()
{
    // srand(time(0));
    srand(123);

    Set<int> mySet;
    for (int i = 0; i < 5; ++i)
    {
        mySet.insert((i + 1) * 10);
    }
    mySet.insert(110); // Collides with 10 in hash table
    mySet.insert(20); // Duplicate, should not be added
    cout << "mySet contents: " << mySet << endl;
    mySet.remove(30);
    cout << "After removing 30, set contents: " << mySet << endl << endl;
    
    Set<string> names({"Alice", "Bob", "Charlotte", "Daniel"});

    cout << "Names set: " << names << endl;
    names.insert("Alice"); // Duplicate, should not be added
    names.insert("Bob");   // Duplicate, should not be added
    cout << "Names set: " << names << endl << endl;

    
    const size_t SIZE = 20;
    vector<int> data(SIZE);
    cout << "[";
    for (int &val : data)
    {
        val = rand() % 50 + 1; 
        cout << val;
        if (&val != &data[SIZE - 1])
        {
            cout << ",";
        }
    }
    cout << "]\n";
    cout << "anyDuplicates():" << endl;
    cout << boolalpha;
    cout << anyDuplicates(data) << endl;
    vector<int> data2 = {1,2,3,4,5};
    cout << anyDuplicates(data2) << endl << endl;

    cout << "uniqueString():" << endl;
    cout << uniqueString("abcdefg") << endl;
    cout << uniqueString("hello") << endl << endl;

    cout << "twoSum():" << endl;
    vector<int> data3 = {10,15,3,7};
    cout << twoSum(data3, 17) << endl;
    cout << twoSum(data3, 20) << endl << endl;

    cout << "isAnagram():" << endl;
    cout << isAnagram("listen", "silent") << endl;
    cout << isAnagram("hello", "world") << endl << endl;
    
    return 0;
}