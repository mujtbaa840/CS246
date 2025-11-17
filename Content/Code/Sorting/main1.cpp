#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void Swap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void printVector(const std::vector<T>& vec)
{
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i < vec.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

/* Selection Sort */
/*
    For I = 0 to n-2
        MinIndex = I
        For J = I+1 to n-1
            If A[J] < A[MinIndex]
                MinIndex = J
        Swap A[I] and A[MinIndex]
*/
template <typename T>
void selectionSort(vector<T>& arr)
{
    
}

/* Insertion Sort */
/*
    For I = 1 to n-1
        Key = A[I]
        J = I
        While J > 0 and A[J-1] > Key
            A[J] = A[J-1]
            J = J - 1
        A[J] = Key
*/
template <typename T>
void insertionSort(vector<T>& arr)
{
    
}

/* Bubble Sort */
/*
    For I = 0 to n-2
        Swapped = false
        For J = 0 to n-I-2
            If A[J] > A[J+1]
                Swap A[J] and A[J+1]
                Swapped = true
        If not Swapped
            Break
*/
template <typename T>
void bubbleSort(vector<T>& arr)
{
    
}



int main()
{
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    selectionSort(arr1);
    cout << "Selection Sort: ";
    printVector(arr1);

    vector<int> arr2 = {64, 34, 25, 12, 22, 11, 90};
    insertionSort(arr2);
    cout << "Insertion Sort: ";
    printVector(arr2);

    vector<int> arr3 = {64, 34, 25, 12, 22, 11, 90};
    bubbleSort(arr3);
    cout << "Bubble Sort: ";
    printVector(arr3);

    vector<char> arr4 = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    selectionSort(arr4);
    cout << "Selection Sort: ";
    printVector(arr4);

    vector<char> arr5 = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    insertionSort(arr5);
    cout << "Insertion Sort: ";
    printVector(arr5);

    vector<char> arr6 = {'j', 'i', 'h', 'g', 'f', 'e', 'd', 'c', 'b', 'a'};
    bubbleSort(arr6);
    cout << "Bubble Sort: ";
    printVector(arr6);

    return 0;
}