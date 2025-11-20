#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void merge(vector<T>& arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;                
    int n2 = right - mid;

    vector<T> L(n1);
    vector<T> R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else // L[i] > R[j]
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right)
{
    if (left < right)                           
    {
        int mid = left + (right - left) / 2;    

        mergeSort(arr, left, mid);              
        mergeSort(arr, mid + 1, right);         

        merge(arr, left, mid, right);           
    }
}

template <typename T>
void print(const vector<T>& arr)
{
    cout << "[";
    for (int i = 0; i < arr.size(); i++)
    {
        if (i != 0)
        {
            cout << ", ";
        }
        cout << arr[i];
    }
    cout << "]";
}

int main()
{
    vector<int> arr = {10,1,8,11,16,7,2,3,5,15,12,13,9,6,14,4};

    print(arr);
    cout << endl;

    mergeSort(arr, 0, 15);

    print(arr);
    cout << endl;

}