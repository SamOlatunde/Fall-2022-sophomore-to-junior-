//**************************************************************
// Calvin Leavy
// Samuel Olatunde
// Advanced Algorithms Date: (11/07/2022)
//***************************************************************
// This Program Implements and times the Quick Sort Algorithm
// with a data set in ascending order. The goal, is to 
// understand how the size and order of the data set affects 
// the time complexity and running time of the algorithm in 
// comparison to other sorting algorithms.Input is from file, 
// and output is made to the screen.
// Note: This program uses outsourced proceedures, appriopiate
// referencing is provided at definition
//*****************************************************************
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<chrono>

using namespace std::chrono;
using namespace std;

const int N = 25000;

//Function Prototypes
void swap(int* a, int* b);
void quickSortIterative(int arr[], int l, int h);
int partition(int arr[], int l, int h);

int main()
{
    // Variable declarations
    int* array = new int[N];
    ifstream infile("C:\\AscendingOrder.txt");

    // reads input from the file and stores in corresponding array
    // element 
    for (int i = 0; i < N; i++)
    {
        infile >> array[i];
    }

    // captures the time just before we initiate the algorithm
    auto start = high_resolution_clock::now();

    // launches quick sort algortihm
    quickSortIterative(array, 0, N - 1);

    // captures the time just after we terminate the algorithm and
    // return to calling function
    auto stop = high_resolution_clock::now();

    // computes difference between start and stop time, and
    // converts answer to microseconds 
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Quick Sort sort time for ascending order: "
        << duration.count() << " microseconds\n";

    //memory deallocation
    delete[] array;
    array = NULL;

    //close file 
    infile.close();
    return 0;
}

//*******************************************************************
// Name:: partition()
// Parameters: 1 it array, 2 ints
// Source:
//  https://www.geeksforgeeks.org/c-program-for-iterative-quick-sort/
// This function is a subrountine of the quicksort algorithm, it does 
// most of the heavy lifting of the algorithm.
//********************************************************************
int partition(int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}

//*******************************************************************
// Name:: quickSortIterative()
// Parameters: 1 it array, 2 ints
// Source:
//  https://www.geeksforgeeks.org/c-program-for-iterative-quick-sort/
// This function implements the iterative version of the Quick Sort 
// Algorithm using an auxiliary stack. 
//********************************************************************
void quickSortIterative(int arr[], int l, int h)
{
    // Create an auxiliary stack
    int* stack = new int[h - l + 1];

    // initialize top of stack
    int top = -1;

    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;

    // Keep popping from stack while is not empty
    while (top >= 0)
    {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];

        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);

        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }

        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }

    delete[] stack;
}

//*******************************************************************
// Name:: swap()
// Parameters: 2 int pointers
// This function swaps the values of two integer memory locations
//********************************************************************
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}