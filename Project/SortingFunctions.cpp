/*
    Grossi Mara 
*/

#include <iostream>
using namespace std;

struct positions
{
    int l;  // per salvare less
    int g;  // per salvare greater
};

void countingSort(int* toOrderArray, size_t size);
int real_max(int* A, size_t size);
int real_min(int* A, size_t size);
void quickSort(int* toOrderArray, size_t size);
void quickSort_Rec(int* toOrderArray, int low, int high);
int partition_1(int* toOrderArray, int low, int high);
void quickSort_3_ways(int* toOrderArray, size_t size);
void quickSort_3_ways_Rec(int* toOrderArray, int low, int high);
positions partition_2(int* toOrderArray, int low, int high);
void insertionSort(int* toOrderArray, size_t size);
void swap(int* A, int p, int q);

// _________________________________________ CountingSort _________________________________________

void countingSort(int* toOrderArray, size_t size)
{
    int max = real_max(toOrderArray, size);
    int min = real_min(toOrderArray, size);

    int count_size = max - min + 1;
    int count[count_size];
    int aux[size];    

    for(int i = 0; i < count_size; i++)
    {
        count[i] = 0;
    }

    for(int i = 0; i < size; i++)  
    { 
        count[toOrderArray[i]- min]++;
    }

    for(int i = 1; i < count_size; i++)  
    {
        count[i] += count[i - 1];   
    }

    for(int i = size - 1; i >= 0; i--)  
    {
        aux[count[toOrderArray[i] - min] - 1] = toOrderArray[i]; 
        count[toOrderArray[i] - min]--;
    }

    for(int i = 0; i < size; i++)
    {
        toOrderArray[i] = aux[i];
    }
}

int real_max(int* A, size_t size)
{
    int max = A[0];

    for(int i = 1; i < size; i++)
    {
        if(max < A[i])
        {
            max = A[i];
        }
    }

    return max;
}

int real_min(int* A, size_t size)
{
    int min = A[0];

    for(int i = 1; i < size; i++)
    {
        if(min > A[i])
        {
            min = A[i];
        }
    }

    return min;
}

// _________________________________________ QuickSort _________________________________________

void quickSort(int* toOrderArray, size_t size)
{
    quickSort_Rec(toOrderArray, 0, size - 1);
}

void quickSort_Rec(int* toOrderArray, int low, int high)
{
    if(low < high)
    {
        int newPivotPosition = partition_1(toOrderArray, low, high);
        quickSort_Rec(toOrderArray, low, newPivotPosition - 1);
        quickSort_Rec(toOrderArray, newPivotPosition + 1, high);
    }
}

int partition_1(int* toOrderArray, int low, int high)
{
    int i = low - 1;
    int pivot = toOrderArray[high];

    for(int j = low; j <= high; j++)
    {
        if(toOrderArray[j] <= pivot)
        {
            i++;
            swap(toOrderArray, i, j);
        }
    } 

    return i;   
}

// _________________________________________ QuickSort 3 ways _________________________________________

void quickSort_3_ways(int* toOrderArray, size_t size)
{
    quickSort_3_ways_Rec(toOrderArray, 0, size - 1);
}

void quickSort_3_ways_Rec(int* toOrderArray, int low, int high)
{
    if(low < high)
    {
        positions pos = partition_2(toOrderArray, low, high);

        quickSort_3_ways_Rec(toOrderArray, low, pos.l - 1);
        quickSort_3_ways_Rec(toOrderArray, pos.g + 1, high);
    }
}

positions partition_2(int* toOrderArray, int low, int high)
{
    int middle = (high + low) / 2;
    int pivot = toOrderArray[middle];

    int less = low;
    int equal = low;
    int greater = high;

    while(equal <= greater)
    {
        if(toOrderArray[equal] < pivot)
        {
            swap(toOrderArray, equal, less);
            less++;
            equal++;
        }
        else if(toOrderArray[equal] > pivot)
        {
            swap(toOrderArray, equal, greater);
            greater--;
        }
        else
        {
            equal++;
        }
    }

    return positions{less, greater};   
}

// _________________________________________ InsertionSort _________________________________________

void insertionSort(int* toOrderArray, size_t size)
{
    for(int i = 1; i < size; i++)
    {
        int key = toOrderArray[i];
        int j = i - 1;
        
        while(j >= 0 && toOrderArray[j] > key)
        {
            toOrderArray[j + 1] = toOrderArray[j];
            j--;
        }

        toOrderArray[j + 1] = key;
    }
}

// ______________________________________________________________________________________________________

void swap(int* A, int p, int q)
{
    int* p1 = A + p;
    int* p2 = A + q;
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}