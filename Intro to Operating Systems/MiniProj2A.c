// Name: Samuel Olatunde
// Course: Introduction To Operating Systems - Fall 2022 
// Instructor: Nelson Passos
// Description: 
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#define size 10000
#define NUM_OF_THREADS 5

long TOTAL = 0;

int array[size];

void * addSectionOfArray(void * tid);

int main(int argc, char * argv[])
{
    // initializes the array 
    for (int i = 1; i <= size; i++)
    {
        array[i] = i % 257;
    }

    pthread_t threads[NUM_OF_THREADS];
    int status,i;
    
    
    for ( i = 0; i <= NUM_OF_THREADS; i++)
    {
        status = pthread_create(&threads[i], NULL, addSectionOfArray, (void *)(i+1));
    
        if(status != 0)
        {
            printf("Oops.pthread_create returned error code %d", status);
            exit(-1);
        }
        // isn't this causing sequential execution??
       
    }
    
    pthread_join(threads[i], NULL);
    printf("The value of TOTAL after the execution of all threads is, %d", TOTAL);

    
    return 0; 
}

void * addSectionOfArray(void * tid)
{
    int * t = (int *)tid;

    for(int i = ((*t-1) *2000); i <= (((*t)*2000)-1); i++)
    {
        TOTAL += array[i];
    }

    pthread_exit(NULL);
}