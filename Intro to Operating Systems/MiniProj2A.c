// Name: Samuel Olatunde, Bao Tang 
// Course: Introduction To Operating Systems - Fall 2022 
// Instructor: Nelson Passos
// Description: Uses Threads to calculate, the sum of numbers
// in an array. The sum is stored in a global variable called 
// TOTAL. 
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#define size 10000
#define NUM_OF_THREADS 5

// accumaltor variable 
long TOTAL = 0;

// creates an array of size elements
int array[size];

// Function prototype
void* addSectionOfArray(void* tid);

int main(int argc, char* argv[])
{
    // initializes the array 
    for (int i = 0; i < size; i++)
    {
        array[i] = i % 257;
    }

    // creates an array of threads 
    pthread_t threads[NUM_OF_THREADS];

    // intended use: save the return value of pthread_create
    // so we can check if the operation executed successfully
    int status;

    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        status = pthread_create(&threads[i], NULL,
            addSectionOfArray, (void*)(i + 1));

        // if pthread_create doesn't complete successfully terminate
        // the program and let the user know
        if (status != 0)
        {
            printf("Oops.pthread_create returned error code %d\n",
                status);
            exit(-1);
        }
    }

    // ensures all threads are executed before the program 
    // terminates 
    for (int i = 0; i < NUM_OF_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("The value of TOTAL after the execution ");
    printf("of all threads is, % d\n", TOTAL);

    return 0;
}

// Name: addSectionOfArray
// Purpose: procedure intended for thread execution, 
// each thread is apportioned a chunk of the array
// to sum up and all threads store their result 
// in the global variable, TOTAL.
// Parameters: 1 void pointer, indicating the 
// thread id
void* addSectionOfArray(void* tid)
{
    int t = tid;

    for (int i = ((t - 1) * 2000); i <= (((t) * 2000) - 1); i++)
    {
        TOTAL += array[i];
    }

    pthread_exit(NULL);
}