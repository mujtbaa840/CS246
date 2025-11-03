#include <iostream>
#include <vector>
#include "Set.h"


using namespace std;
using namespace dsc;

template <typename T>
// using Set = SetOpen<T>;
using Set = SetChain<T>;

int main()
{
    Set<int> mySet;
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);
    mySet.insert(40);
    mySet.insert(50);
    mySet.insert(110); // Collides with 10 in hash table
    mySet.insert(20); // Duplicate, should not be added
    cout << "Set contents: " << mySet << endl;
    mySet.remove(30);
    cout << "After removing 30, set contents: " << mySet << endl;
    cout << "Set contains 20: " << (mySet.contains(20) ? "Yes" : "No") << endl;
    cout << "Set contains 30: " << (mySet.contains(30) ? "Yes" : "No") << endl;
    
    Set<string> names;
    names.insert("Alice");
    names.insert("Bob");
    names.insert("Charlotte");
    names.insert("Daniel");
    names.insert("Alice"); // Duplicate, should not be added
    names.insert("Bob");   // Duplicate, should not be added
    cout << "Names set: " << names << endl;

    return 0;
}