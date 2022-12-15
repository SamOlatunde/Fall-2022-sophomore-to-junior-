//*****************************************************************
// End of Semester Project 
// Name: Samuel Olatunde , and Sunil Rasaily 
// GPU Programming Date: Date of Submission (11/28/2022)
//******************************************************************
// 
// 
//******************************************************************
#include<stdio.h>
#include<cuda.h>
#include"timer.h"

//error tolerance 
#define eT

// data size
#define N  4

// limit for the max number of iterations
#define limit 4




void calcIntTempDistribution(float * A, float * b);
bool converged (float newValue, float oldValue );

int main()
{


    return 0;
}



//*******************************************************************
// Name::calcIntTempDistribution()
// Parameters: 2 float pointers
//
//********************************************************************
void calcIntTempDistribution(float * g, float * h)
{
   int iteration = 0;

   do 
   {
      for (int i = 1; i < (N-1); i++)
      {
        for(int j = 1; j < (N-1); j++)
        {
           g[i][j] = 0.25 * (h[i-1][j] + h[i+1][j]+h[i][j-1]+h[i][j+1]);
        }
      }
      
      bool continue  = false;
      for (int i = 1; i < (N-1); i++)
      {
        for (int j = 1<(N-1); j++)
        {
            if(!converged(g[i][j],h[i][j]))
            {
                continue = true;
            }

            h[i][j] = g[i][j];

        }
      }

   }while(continue == true)
}

//*******************************************************************
// Name::converged()
// Parameters: 2 floats
// Tests for convergence of two points. Returns true if the error is 
// within error tolerance; false otherwise 
//********************************************************************
bool converged (float newValue, float oldValue )
{
    float er = (newValue-oldValue)/newValue;
    if (er < 0) er = -er;

    return (er < eT);
}