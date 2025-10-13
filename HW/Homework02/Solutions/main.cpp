#include <iostream>
#include <string>
#include <vector>

#include <cmath>

using namespace std;

string toBase(int number, int base = 2) // T(n): n = number
{
    if (!number) // 1
    {
        return "0"; // 0
    }
    string lookup = "0123456789ABCDEF"; // 1 ... (Actually about 40, but constant. For simplicity, we say 1)
    string result = ""; // 1
    while (number > 0) // log_base(n) + 2 ... (Actually floor(log_base(n)) + 2, but we drop the floor for simplicity)
    {
        result = lookup[number % base] + result; // (log_base(n) + 1) * 5 ... (number % base is 1, lookup[i] is *(lookup + i) which is 2, string + string is 1, result = string is 1)
        number /= base; // (log_base(n) + 1) + 2 ... (division is 1, assignment is 1)
    }
    return result; // 1
}
/*
    T(n) = 1 + 1 + 1 + log(n) + 2 + 5log(n) + 5 + 2log(n) + 2 + 1
        = 8log(n) + 13
    O(log(n))

*/

bool isPrime(int number) // T(n): n = number
{
    if (number <= 1) // 1
    {
        return false; // 0
    }
    for (int i = 2; i * i <= number; i++) // 1 + sqrt(n) + sqrt(n) - 1 ... (initialization is 1, condition is checked sqrt(n) times, increment is done sqrt(n) - 1 times)
    {
        if (!(number % i)) // sqrt(n) - 1
        {
            return false; // 0
        }
    }
    return true; // 1
}
/*
    T(n) = 1 + 2sqrt(n) + sqrt(n) - 1 + 1
        = 3sqrt(n) + 1
    O(sqrt(n))
*/

int* letterCount(const string& str) // T(n): n = str.length()
{
    int* counts = new int[26](); // 28 ... (allocation is 1, initialization of 26 elements is 26, assignment is 1)
    for (int i = 0; i < str.length(); i++) // 1 + n + n + 1 ... (initialization is 1, condition is checked n + 1 times, increment is done n times)
    {
        char c = toupper(str[i]); // n * 4 ... (str[i] is *(str + i) which is 2, toupper is 1, assignment is 1)
        if (c >= 'A' && c <= 'Z') // n
        {
            counts[c - 'A']++; // n * 4 ... (c - 'A' is 1, counts[i] is *(counts + i) which is 2, increment is 1)
        }
    }
    return counts; // 1
}
/*
    T(n) = 28 + 1 + n + n + 1 + 4n + n + 4n + 1
        = 10n + 31
    O(n)
*/

int sumArray(int arr[]) // T(n): n = 26 (constant)
{
    int sum = 0; // 1
    for (int i = 0; i < 26; i++) // 1 + 26 + 26 + 1 ... (initialization is 1, condition is checked 27 times, increment is done 26 times)
    {
        sum += arr[i]; // 26 * 4 ... (arr[i] is *(arr + i) which is 2, addition is 1, assignment is 1)
    }
    return sum; // 1
}
/*
    T(n) = 1 + 1 + 26 + 26 + 1 + 4 * 26 + 1
        = 6 * 26 + 4
        = 160
    O(1)
*/

vector<int> Union(const vector<int>& a, const vector<int>& b) // T(n,m): n = a.size(), m = b.size()
{
    vector<int> result = a; // n + 1 ... (copying a is n, assignment is 1)
    for (int i = 0; i < b.size(); i++) // 1 + m + m + 1 ... (initialization is 1, condition is checked m + 1 times, increment is done m times)
    {
        bool found = false; // m
        for (int j = 0; j < a.size(); j++) // m * (1 + n + n + 1) 
        {
            if (b[i] == a[j]) // m * n
            {
                found = true; // m
                break; // m
            }
        }
        if (!found) // m
        {
            result.push_back(b[i]); // m * (1 + 1 + 1) ... (b[i] is *(b + i) which is 2, push_back is 1)
        }
        return result; // 1
    }
       
}

/*
    T(n,m) = n + 1 + 1 + m + m + 1 + m + m * (1 + 2n + 1) + m + m + m * 3 + 1
        = n + 8m + m * (2n + 2) + 1
        = n + 10m + 2mn + 1
    O(mn)
*/