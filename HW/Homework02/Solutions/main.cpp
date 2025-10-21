#include <iostream>
#include <string>
#include <vector>

#include <cmath>

using namespace std;

string toBase(int number, int base = 2)             // T(n): n = number
{
    if (!number)                                    // 1
    {
        return "0";                                 // 0
    }
    string lookup = "0123456789ABCDEF";             // 1 
    string result = "";                             // 1
    while (number > 0)                              // floor(log_base(n)) + 2
    {
        result = lookup[number % base] + result;    // floor(log_base(n)) + 1
        number /= base;                             // floor(log_base(n)) + 1
    }
    return result;                                  // 1
}
/*
    T(n) = c1 + c3 + c4 + c5(floor(log_base(n)) + 2) + c6(floor(log_base(n)) + 1) + c7(floor(log_base(n)) + 1) + c8
         = (c5 + c6 + c7)floor(log_base(n)) + (c1 + c3 + c4 + 2c5 + c6 + c8)
         = 3log_base(n) + 7
    O(log(n))
*/

bool isPrime(int number)                    // T(n): n = number
{
    for (int i = 2; i * i <= number; i++)   // 1 + floor(sqrt(n)) + floor(sqrt(n)) - 1
    {
        if (!(number % i))                  // floor(sqrt(n)) - 1
        {
            return false;                   // 0
        }
    }
    return number > 1;                      // 1
}
/*
    T(n) = c1 + c2(floor(sqrt(n)) + c3(floor(sqrt(n)) - 1) + c5(floor(sqrt(n)) - 1) + c6
         = (c2 + c3 + c5)floor(sqrt(n)) + (c1 - c3 - c5 + c6)
         = 3floor(sqrt(n))
    O(sqrt(n))
*/

int* letterCount(const string& str)         // T(n): n = str.length()
{
    static int counts[26] = {0};            // 1
    for (int i = 0; i < str.length(); i++)  // 1 + n + 1 + n 
    {
        char c = toupper(str[i]);           // n
        if (c >= 'A' && c <= 'Z')           // n
        {
            counts[c - 'A']++;              // n
        }
    }
    return counts;                          // 1
}
/*
    T(n) = c1 + c2 + c3(n+1) + c4(n) + c5(n) + c6(n) + c7(n) + c8
         = (c3 + c4 + c5 + c6 + c7)n + (c1 + c2 + c3 + c8)
         = 5n + 4
    O(n)
*/

int sumArray(int arr[])             // T(n): n = 26 (constant)
{
    int sum = 0;                    // 1
    for (int i = 0; i < 26; i++)    // 1 + 26 + 1 + 26 
    {
        sum += arr[i];              // 26
    }
    return sum;                     // 1
}
/*
    T(n) = c1 + c2 + c3(26 + 1) + c4(26) + c5(26) + c6
        = (c3 + c4 + c5)26 + (c1 + c2 + c3 + c6)
        = 3*26 + 4
        = 82
    O(1)
*/

vector<int> Union(const vector<int>& a, const vector<int>& b)   // T(n,m): m = a.size(), n = b.size()
{
    vector<int> result = a;                                     // m
    for (int i = 0; i < b.size(); i++)                          // 1 + n + 1 + n 
    {
        bool found = false;                                     // n
        for (int j = 0; j < a.size(); j++)                      // n + mn + n + mn 
        {
            if (b[i] == a[j])                                   // mn
            {
                found = true;                                   // 0
                break;                                          // 0
            }
        }
        if (!found)                                             // n
        {
            result.push_back(b[i]);                             // 1
        }
    }
    return result;                                              // 1
}
/*
    T(m.n) = c1(m) + c2 + c3(n + 1) + c4(n) + c5(n) + c6(mn + n) + c7(mn) + c8(mn) + c9(n) + c10 + c11(n) + c12
           = (c6 + c7 + c8)mn + c1(m) + (c3 + c4 + c5 + c6 + c9 + c11)n + (c2 + c3 + c10 + c12)
           = 3mn + m + 6n + 4
    O(mn)
*/