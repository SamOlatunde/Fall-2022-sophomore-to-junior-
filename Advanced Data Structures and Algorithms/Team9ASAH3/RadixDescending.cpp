//***************************************************************
// Calvin Leavy
// Samuel Olatunde
// Advanced Algorithms Date: (11/07/2022)
//***************************************************************
// This Program Implements and times the Radix Sort Algorithm
// with a data set in descending order. The goal, is to 
// understand how the size and order of the data set affects 
// the time complexity and running time of the algorithm in 
// comparison to other sorting algorithms.Input is from file, 
// and output is made to the screen.
// Note: This program uses outsourced proceedures, appriopiate
// referencing is provided at definition
//***************************************************************
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

const int arraySize = 25000;

//Function Prototypes
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);
void radixsort(int arr[], int n);

int main()
{
    // Variable Declarations
    int* array = new int[arraySize];
    ifstream infile("C:\\DescendingOrder.txt");

    // reads input from the file and stores in corresponding array
    // element 
    for (int i = 0; i < arraySize; i++)
    {
        infile >> array[i];
    }

    // captures the time just before we initiate the algorithm
    auto start = high_resolution_clock::now();

    // launches algortihm
    radixsort(array, arraySize);

    // captures the time just after we terminate the algorithm and
    // return to calling function
    auto stop = high_resolution_clock::now();

    // computes difference between start and stop time, and
    // converts answer to microseconds 
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Radix Sort sort time for descending order: "
        << duration.count() << " microseconds\n";

    // memory deallocation
    delete[] array;
    array = NULL;

    // close file
    infile.close();

    return 0;
}

//*******************************************************************
// Name:: getMax()
// Parameters: 1 int array, 1 integer 
// Source: https://www.geeksforgeeks.org/radix-sort/
// This function returns the largest number in an array
//********************************************************************
int getMax(int arr[], int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

//*******************************************************************
// Name:: countSort
// Parameters: 1 int array, 1 integer
// Source: https://www.geeksforgeeks.org/radix-sort/ 
// This function implements the counting sort algorithm.It is used by
// the radix sort algorithm to sort the digits at each place value 
// of all elements on initial array.
//********************************************************************
void countSort(int arr[], int n, int exp)
{
    // output array
    int* output = new int[arraySize]; 
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    delete[] output;
    output = NULL;
}

//*******************************************************************
// Name:: radixSort()
// Parameters: 1 int array, 1 integer
// Source: https://www.geeksforgeeks.org/radix-sort/
// This function implements the radix sort algorithm
//********************************************************************
void radixsort(int arr[], int n)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}
