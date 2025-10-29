#include <iostream>
#include <string>
#include <vector>

using namespace std;

unsigned int factorial(unsigned int n)
{
    if (n <= 1)                    // 1     
    {
        return 1;                  // 0    
    }
    return n * factorial(n - 1);   // 1 + 2(n - 1)     
}
/*
    T(n) = 1 + 1 + 2n - 2
         = 2n - 2 + 2
         = 2n
    Big-O = O(n)
    n is the value of the input number
*/
/*
    T(n): 1 + (1 + T(n-1)) => 1 + (1 + 2(n-1)) = 2n
    T(5): 1 + (1 + T(4)) => 1 + (1 + 8) = 10
    T(4): 1 + (1 + T(3)) => 1 + (1 + 6) = 8
    T(3): 1 + (1 + T(2)) => 1 + (1 + 4) = 6
    T(2): 1 + (1 + T(1)) => 1 + (1 + 2) = 4
    T(1): 1 + 1 = 2
*/
/*
    factorial(n): 1 + (1 + factorial(n-1)) => 1 + (1 + 2(n-1)) = 2n
    factorial(5): 1 + (1 + factorial(4)) => 1 + (1 + 8) = 10
    factorial(4): 1 + (1 + factorial(3)) => 1 + (1 + 6) = 8
    factorial(3): 1 + (1 + factorial(2)) => 1 + (1 + 4) = 6
    factorial(2): 1 + (1 + factorial(1)) => 1 + (1 + 2) = 4
    factorial(1): 1 + 1 = 2
*/

unsigned int digitCount(unsigned int n)
{
    if (n < 10)                       // 1 
    {
        return 1;                     // 0  
    }
    return 1 + digitCount(n / 10);    // 1 + 
}
/*
    T(n) = 1 + 1 + 2⌊log₁₀(n)⌋
         = 2⌊log₁₀(n)⌋ + 2
    Big-O = O(log(n))
    n is the value of the input number
*/
/*
    T(n): 1 + (1 + T(n/10)) => 1 + (1 + 2⌊log₁₀(n)⌋) = 2⌊log₁₀(n)⌋ + 2
    T(20251): 1 + (1 + T(2025)) => 1 + (1 + 8) = 10
    T(2025): 1 + (1 + T(202)) => 1 + (1 + 6) = 8
    T(202): 1 + (1 + T(20)) => 1 + (1 + 4) = 6
    T(20): 1 + (1 + T(2)) => 1 + (1 + 2) = 4
    T(2): 1 + 1 = 2
*/
/*
    digitCount(n): 1 + (1 + digitCount(n/10)) => 1 + (1 + 2⌊log₁₀(n)⌋) = 2⌊log₁₀(n)⌋ + 2
    digitCount(20251): 1 + (1 + digitCount(2025)) => 1 + (1 + 8) = 10
    digitCount(2025): 1 + (1 + digitCount(202)) => 1 + (1 + 6) = 8
    digitCount(202): 1 + (1 + digitCount(20)) => 1 + (1 + 4) = 6
    digitCount(20): 1 + (1 + digitCount(2)) => 1 + (1 + 2) = 4
    digitCount(2): 1 + 1 = 2
*/

template <class T>
class Node
{
    public:
        T data;
        Node<T>* next;
        Node(const T& value) : data(value), next(nullptr) {}
};
bool contains(Node<int>* node, int target)
{
    if (node == nullptr)                  // 1
    {
        return false;                     // 0
    }
    if (node->data == target)             // 1
    {
        return true;                      // 0
    }
    return contains(node->next, target);  // 2n
}
/*
    T(n) = 1 + 1 + 2n
         = 2n + 2
    Big-O = O(n)
    n is the number of nodes in the linked list
*/
/*  node0 -> node1 -> node2 -> node3 -> nullptr
    T(n): 1 + 1 + T(n-1) => 1 + 1 + 2n
    T(4): 1 + 1 + T(3) => 1 + 1 + 8 = 10
    T(3): 1 + 1 + T(2) => 1 + 1 + 6 = 8
    T(2): 1 + 1 + T(1) => 1 + 1 + 4 = 6
    T(1): 1 + 1 + T(0) => 1 + 1 + 2 = 4
    T(0): 1 + 1 = 2
*/
/*  node0 -> node1 -> node2 -> node3 -> nullptr
    contains(node, target): 1 + 1 + contains(node->next, target) => 1 + 1 + 2n
    contains(node0, target): 1 + 1 + (contains(node1, target)) => 1 + 1 + 8 = 10
    contains(node1, target): 1 + 1 + (contains(node2, target)) => 1 + 1 + 6 = 8
    contains(node2, target): 1 + 1 + (contains(node3, target)) => 1 + 1 + 4 = 6
    contains(node3, target): 1 + 1 + (contains(nullptr, target)) => 1 + 1 + 2 = 4
    contains(nullptr, target): 1 + 1 = 2
*/

void printBinaries(int num, const string& b = "")
{
    if (b.length() == num)           // 1
    {
        cout << b << endl;           // 0
        return;
    }
    printBinaries(num, b + "0");     // 2ⁿ + 2ⁿ⁻¹ - 1 = 3(2ⁿ⁻¹) - 1
    printBinaries(num, b + "1");     // 2ⁿ + 2ⁿ⁻¹ - 1 = 3(2ⁿ⁻¹) - 1
}
/*
    T(n) = 1 + 2(2ⁿ + 2ⁿ⁻¹ - 1)
         = 2ⁿ⁺¹ + 2ⁿ - 2 + 1
         = (2ⁿ)(2 + 1) - (2 - 1)
         = 3(2ⁿ) - 1
    Big-O = O(2ⁿ)
    n is the num - b.length(). The length of the binary strings being printed minus the length of the current string.

*/
/*  x = num, y = b.length()
    T(n) = T(x - y)

    T(n): 1 + (T(n-1) + T(n-1)) = 1 + (3(2ⁿ⁻¹) - 1 + 3(2ⁿ⁻¹) - 1) = 3(2ⁿ) - 1
    T(4): 1 + (T(3) + T(3)) = 1 + (23 + 23) = 47
    T(3): 1 + (T(2) + T(2)) = 1 + (11 + 11) = 23
    T(2): 1 + (T(1) + T(1)) = 1 + (5 + 5) = 11
    T(1): 1 + (T(0) + T(0)) = 1 + (2 + 2) = 5
    T(0): 1 + 1 = 2
*/
/*
    printBinaries(num, b): 1 + (printBinaries(num, b + "0") + printBinaries(num, b + "1")) => 1 + ((2ⁿ + 2ⁿ⁻¹ - 1) + (2ⁿ + 2ⁿ⁻¹ - 1)) = 3(2ⁿ) - 1
    printBinaries(4, ""): 1 + (printBinaries(4, "0") + printBinaries(4, "1")) => 1 + (23 + 23) = 47
    printBinaries(4, "0"): 1 + (printBinaries(4, "00") + printBinaries(4, "01")) => 1 + (11 + 11) = 23
    printBinaries(4, "1"): 1 + (printBinaries(4, "10") + printBinaries(4, "11")) => 1 + (11 + 11) = 23
    printBinaries(4, "00"): 1 + (printBinaries(4, "000") + printBinaries(4, "001")) => 1 + (5 + 5) = 11
    printBinaries(4, "01"): 1 + (printBinaries(4, "010") + printBinaries(4, "011")) => 1 + (5 + 5) = 11
    printBinaries(4, "10"): 1 + (printBinaries(4, "100") + printBinaries(4, "101")) => 1 + (5 + 5) = 11
    printBinaries(4, "11"): 1 + (printBinaries(4, "110") + printBinaries(4, "111")) => 1 + (5 + 5) = 11
    printBinaries(4, "000"): 1 + (printBinaries(4, "0000") + printBinaries(4, "0001")) => 1 + (2 + 2) = 5
    printBinaries(4, "001"): 1 + (printBinaries(4, "0010") + printBinaries(4, "0011")) => 1 + (2 + 2) = 5
    printBinaries(4, "010"): 1 + (printBinaries(4, "0100") + printBinaries(4, "0101")) => 1 + (2 + 2) = 5
    printBinaries(4, "011"): 1 + (printBinaries(4, "0110") + printBinaries(4, "0111")) => 1 + (2 + 2) = 5
    printBinaries(4, "100"): 1 + (printBinaries(4, "1000") + printBinaries(4, "1001")) => 1 + (2 + 2) = 5
    printBinaries(4, "101"): 1 + (printBinaries(4, "1010") + printBinaries(4, "1011")) => 1 + (2 + 2) = 5
    printBinaries(4, "110"): 1 + (printBinaries(4, "1100") + printBinaries(4, "1101")) => 1 + (2 + 2) = 5
    printBinaries(4, "111"): 1 + (printBinaries(4, "1110") + printBinaries(4, "1111")) => 1 + (2 + 2) = 5
    printBinaries(4, "0000"): 1 + 1 = 2
    printBinaries(4, "0001"): 1 + 1 = 2
    printBinaries(4, "0010"): 1 + 1 = 2
    printBinaries(4, "0011"): 1 + 1 = 2
    printBinaries(4, "0100"): 1 + 1 = 2
    printBinaries(4, "0101"): 1 + 1 = 2
    printBinaries(4, "0110"): 1 + 1 = 2
    printBinaries(4, "0111"): 1 + 1 = 2
    printBinaries(4, "1000"): 1 + 1 = 2
    printBinaries(4, "1001"): 1 + 1 = 2
    printBinaries(4, "1010"): 1 + 1 = 2
    printBinaries(4, "1011"): 1 + 1 = 2
    printBinaries(4, "1100"): 1 + 1 = 2
    printBinaries(4, "1101"): 1 + 1 = 2
    printBinaries(4, "1110"): 1 + 1 = 2
    printBinaries(4, "1111"): 1 + 1 = 2
*/



int main()
{
    cout << "Factorial of 5: " << factorial(5) << endl; // 120
    cout << "Digit count of 20251: " << digitCount(20251) << endl; // 5
    Node<int>* head = new Node<int>(3);
    head->next = new Node<int>(7);
    head->next->next = new Node<int>(10);
    cout << "Contains 7: " << (contains(head, 7) ? "true" : "false") << endl; // true
    cout << "Contains 4: " << (contains(head, 4) ? "true" : "false") << endl; // false
    cout << "Binary strings of length 4:" << endl;
    printBinaries(4);

    while (head != nullptr)
    {
        Node<int>* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}