//**************************************************************
// Assignment #2
// Name: Samuel Olatunde , and Sunil  Rasaily
// GPU Programming Date: Date of Submission (11/04/2022)
//***************************************************************
// Place your general program documentation here. It should
// be quite a few lines explaining the programs duty carefully.
// It should also indicate how to run the program and data
// input format, filenames etc
//*****************************************************************
#include<stdio.h>
#define _USE_MATH_DEFINES 
#include<math.h>
#define N  8192


struct complexNum
{
  double real;
  double imag;
};



void calcCooleyTukey(struct complexNum * FFT,  struct complexNum * timeDomain);

int main(int argc, char * argv[])
{
    struct complexNum FFT[N];
    struct complexNum timeDomain[N];

    //Hard Coding first * entries of time domain 
    timeDomain[0].real = 3.6;
    timeDomain[0].imag = 2.6;
    timeDomain[1].real = 2.9;
    timeDomain[1].imag = 6.3;
    timeDomain[2].real = 5.6;
    timeDomain[2].imag = 4;
    timeDomain[3].real = 4.8;
    timeDomain[3].imag = 9.1;
    timeDomain[4].real = 3.3;
    timeDomain[4].imag = 0.4;
    timeDomain[5].real = 5.9;
    timeDomain[5].imag = 4.8;
    timeDomain[6].real = 5;
    timeDomain[6].imag = 2.6;
    timeDomain[7].real = 4.3;
    timeDomain[7].imag = 4.1;

    // initializing the other entries of time domain to 0
    for (int i = 8; i < N; i++)
    {
        timeDomain[i].real = 0;
        timeDomain[i].imag = 0;
    }
    
    calcCooleyTukey(FFT,timeDomain);
  
    printf("TOTAL PROCESSED SAMPLES: %d\n", N);
    printf("===========================================\n");
    printf("XR[0]: %f\t", FFT[0].real);
    printf("XI[0]: %f\n", FFT[0].imag);
    printf("===========================================\n");
    for(int i =1; i < N; i++)
    {
       printf("XR[%d]: %f\tXI[%d]: %f\n", i, FFT[i].real, i, FFT[i].imag);// %f\t\t", FFT[0].real);
    }
    printf("===========================================\n\n");
    
    /*printf("XR[3570]: %f\t XI[3570]: %f\n",FFT[3570].real, FFT[3570].imag);
    printf("XR[7666]: %f\t XI[7666]: %f\n",FFT[7666].real, FFT[7666].imag);*/

    return 0; 
}

//*******************************************************************
// Name::calcCooleyTukey()
// Parameters: 2 complexNum Pointers, and 1 int 
// A discussion of what the method/function does and required
// parameters as well as return value.
//CODE MUST HAVE COMMENTS, GOOD AND INFORMATIVE COMMENTS [-10 IF IGNORED]
//********************************************************************
void calcCooleyTukey(struct complexNum * FFT, struct complexNum * timeDomain)
{
    double real;
    double imag;
    double theta;
    float real2ndHalf = 0.0, imag2ndHalf = 0.0, theta2ndHalf = 0.0;
    for (int k = 0; k < (N/2); k++)
    {
        real = 0;
        imag = 0;
        theta = 0;
        real2ndHalf = 0.0, imag2ndHalf = 0.0, theta2ndHalf = 0.0;
        for(int n = 0; n < (N); n ++)
        {
            //theta = ((2 * M_PI) * 2 * n * k) / N;
            theta = ((2 * M_PI) * n * k) / N;
            
            real += (timeDomain[(n)].real * cos(theta) ) + (timeDomain[(n)].imag * sin(theta));
            imag += (-(timeDomain[(n) ].real) * sin(theta)) + (timeDomain[n ].imag * cos(theta));
            // dft of even indexed time domain
            /*real += (timeDomain[(2*n)].real * cos(theta) ) + (timeDomain[(2*n)].imag * sin(theta));
            imag += (-(timeDomain[(2*n)].real) * sin(theta)) + (timeDomain[(2*n)].imag * cos(theta));
            
            theta = ((2 * M_PI) * ((2 * n)+ 1 ) * k) / N;

            // dft of even indexed time domain
            real += (timeDomain[(2*n) + 1].real * cos(theta) ) + (timeDomain[(2*n) + 1].imag * sin(theta));
            imag += (-(timeDomain[(2*n) + 1].real) * sin(theta)) + (timeDomain[(2*n) + 1].imag * cos(theta));*/

            theta2ndHalf = (2 * M_PI * n * (k+(N/2)))/ N;


           real2ndHalf += (timeDomain[(n)].real * cos(theta2ndHalf)) +
                                (timeDomain[(n)].imag * sin(theta2ndHalf));

            imag2ndHalf +=  (-(timeDomain[(n)].real)* sin(theta2ndHalf)) + 
                                (timeDomain[(n)].imag * cos(theta2ndHalf)); 

        }


       FFT[k].real = real;
      FFT[k].imag = imag;

    
     FFT[k + (N/2)].real = real2ndHalf;
    FFT[k + (N/2)].imag = imag2ndHalf;
    }

}
