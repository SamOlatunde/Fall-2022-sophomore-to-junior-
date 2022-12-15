//*****************************************************************
// Assignment #5
// Name: Samuel Olatunde , and Sunil Rasaily 
// GPU Programming Date: Date of Submission (11/07/2022)
//******************************************************************
// This program implements the mathematical operation, 
// convolution(*), which in simple terms is how the shape of one 
// signal is modified by the other(wikipedia). Input is generated in
// program and output is sent to the file 
//******************************************************************
#include<stdio.h>
#define fSize 4096
#define gSize 1024
#define hSize (fSize + gSize - 1)

// Prototype
void computeConvolution(int * f, int* g, int *h);

int main()
{
    // Var4iable declarations
    int f[fSize], g[gSize], h[hSize];
    long long checkSum = 0;

    // Initialize f with values from 1 to 4096 (inclusive)
    for (int i = 0; i < fSize; i++ )
    {
        f[i] = i+1;
    }
    
    // Initialize g with values from 1024 to 1 (inclusive)
    for(int i = gSize-1; i >= 0 ; i--)
    {
        g[gSize - (i+1)] = i +1;
    }
    
    // calculate f(in convolution with)g and place the 
    // result in h
    computeConvolution(f,g,h);
    
    // Performs Check Sum
    for(int i = 0; i < hSize; i++)
    {
        checkSum+= h[i];
    }

    printf("Number of elements in f: %d\n", fSize);
    printf("Number of elements in g: %d\n", gSize);
    printf("Number of elements in h: %d\n", hSize);
    printf("Checksum results: %lld\n", checkSum);
    
    return 0; 
}

//*******************************************************************
// Name:: computeConvolution()
// Parameters: 3 integer pointers to arrays
// This function sequentially computes the resulting signal h 
// of the convolution operation between signals f and g.  
//********************************************************************
void computeConvolution(int * f, int* g, int *h)
{
    int sum = 0;
     
    for (int n = 0; n < hSize; n++ )
    {
        sum = 0;

        for (int m = 0; m <=n; m++)
        {
            // Do not modify sum if the corresponding index of the
            // signals satify the condition for multiplication by zero
            if( m >=0 && m < fSize && ((n-m) >=0) && ((n-m) < gSize))
            {
                sum += (f[m] * g[n-m]);
            }
        }

        h[n] = sum;
    }
}