#include <iostream>
#include <chrono>
using namespace std;

void merge(int* arr, int low, int high, int mid)
{
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
        {
            c[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        arr[i] = c[i];
    }
}

void mergeSort(int* arr, size_t low, size_t high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, high, mid);
    }
    return;
}
int main()
{
    srand(time(NULL));
    int size; 
    cin>>size;
    int* arr = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        int random = rand()%1000;
        arr[i] = random;
    }
    
    auto start = chrono::steady_clock::now();
    mergeSort(arr,0,size-1);
    auto end = chrono::steady_clock::now();

    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i]<< ' ';
     }
    
    cout << "Elapsed time in milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << endl;
    delete[] arr; // ? 
}