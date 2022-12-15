//*****************************************************************
// Assignment #2
// Name: Samuel Olatunde , and Sunil Rasaily 
// GPU Programming Date: Date of Submission (11/04/2022)
//******************************************************************
// This Program Implements a parallel CUDA GPU solution to the 
// computationally intensive Cooley-Tukey FFT Algorithm.The 
// parallel implmentation takes the complexity of the algorithm 
// an order of magnitude lower from O(n^2) to O(n). The program 
// uses a struct to store complex numbers. Input is hard coded and 
// output is sent to a file. 
//******************************************************************
#include<stdio.h>
#include<cuda.h>
#include<math.h>
#define N 8192
#define tileWidth 1024

// struct to handle complex numbers
struct complexNum
{
  float real;
  float imag;
};

// Function Prototype
__global__ 
void calcCooleyTukey(struct complexNum * d_FFT, 
                                 struct complexNum * d_timeDomain);
 
int main()
{
    // host Variable declaration
    struct complexNum FFT[N];
    struct complexNum timeDomain[N];

    //Hard Coding first 8 entries of time domain 
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
    
    // device variables 
    struct complexNum * d_FFT;
    struct complexNum * d_timeDomain;
    int size = N* sizeof(complexNum);
    
    // allocates global memory for device variables
    cudaMalloc((void**) & d_FFT, size);
    cudaMalloc((void**) & d_timeDomain, size);
    
    // Copies data from host to device 
    cudaMemcpy(d_timeDomain, timeDomain, size, cudaMemcpyHostToDevice);

    //Sets grid and block dimensions
    dim3 dimGrid(4,1,1);
    dim3 dimBlock(1024,1,1);

    //Kernel Lauch
    calcCooleyTukey<<<dimGrid, dimBlock>>>(d_FFT, d_timeDomain);

    // copies result from device to host 
    cudaMemcpy(FFT, d_FFT, size, cudaMemcpyDeviceToHost);
    
    //frees allocated memory
    cudaFree(d_FFT);
    cudaFree(d_timeDomain);
    
    // Prints the first 8 samples
    printf("TOTAL PROCESSED SAMPLES: %d\n", N);
    printf("===========================================\n");
    printf("XR[0]: %f\t", FFT[0].real);
    printf("XI[0]: %f\n", FFT[0].imag);
    printf("===========================================\n");
    for(int i =1; i < 8; i++)
    {
       printf("XR[%d]: %f\tXI[%d]: %f\n", i, FFT[i].real,
                                              i, FFT[i].imag);
    }
    printf("===========================================\n\n");
    
    for(int i =4096; i < 4096+8; i++)
    {
       printf("XR[%d]: %f\tXI[%d]: %f\n", i, FFT[i].real,
                                              i, FFT[i].imag);
    }
    printf("===========================================\n\n");
    
    return 0; 
}

//*******************************************************************
// Name::calcCooleyTukey()
// Parameters: 2 complexNum Pointers
// This kernel function computes the FFT for each value of k. The 
// kernel is written for one dimensional grid and blocks, and is 
// written with the assumption that it is launched with a grid size
// that is half of the size of the data set. Each thread takes 
// care of 1 FFT coeficent. Due to the frequency of access of 
// d_timeDomain and the fact that its values don't change throughout 
// execution, the kernel uses the idea of tiling, and shared memory, 
// to reduce the traffic in global memory. This way, each block only 
// has to perform the long latency operation of accessing each 
// d_timeDomain element once, which is when the threads bring the 
// values of d_timeDomain, to shared memory. In addition, the kernel
// uses barrier synchronization, to ensure that all threads have 
// finished a phase before moving on so as to avoid inconsistentcies 
// in our result. 
//********************************************************************
__global__ 
void calcCooleyTukey(struct complexNum * d_FFT, 
                                     struct complexNum * d_timeDomain)
{
    // local to global index mapping 
    int k = blockDim.x * blockIdx.x + threadIdx.x;
    int timeDomainElementsPerThread = N / blockDim.x;
   
   //Allocates shared memory 
   __shared__ struct complexNum tile[tileWidth];
    
    // Variables local to each thread
    float real = 0.0, imag = 0.0, theta = 0.0;
    
    // varibales to compute the other half of array
    float real2ndHalf = 0.0, imag2ndHalf = 0.0, theta2ndHalf = 0.0;

    // Shared memory version  
    // for a given processing window, copy the value of time
    // domain to tile, and compute the values of real and 
    // imag, then move processing window and accumulate 
    // values in real and imag until we have run through the 
    // whole array 
    for (int i = 0; i < timeDomainElementsPerThread; i++)
    {
        tile[threadIdx.x] = d_timeDomain[threadIdx.x + 
                                                      (i* blockDim.x)];
        __syncthreads(); 
        
        for( int n = 0; n < tileWidth; n++)
        {
            //Computation for upper half of d_FFT
            // computes theta for each element of timeDomain.
            // timeDomain index goes up to N, so we need to map
            // the tile index to timeDomain index when we are trying 
            // to compute theta
            theta = (2 * M_PI * (n+ (i* blockDim.x)) * k)/ N;

            //compute and accumulate result in real and imag 
            real += (tile[(n)].real * cos(theta)) +
                                (tile[(n)].imag * sin(theta));
            imag += (-(tile[(n)].real)* sin(theta)) + 
                                (tile[(n)].imag * cos(theta)); 
           
           //Computation for lower half of d_FFT
           theta2ndHalf = (2 * M_PI * (n+ (i* blockDim.x)) * 
                                                      (k+(N/2)))/ N;

           real2ndHalf += (tile[(n)].real * cos(theta2ndHalf)) +
                                (tile[(n)].imag * sin(theta2ndHalf));

            imag2ndHalf +=  (-(tile[(n)].real)* sin(theta2ndHalf)) + 
                                (tile[(n)].imag * cos(theta2ndHalf)); 
        }
        __syncthreads();
    }

    // store result at appropriate location
    d_FFT[k].real = real;
    d_FFT[k].imag = imag;

    d_FFT[k + (N/2)].real = real2ndHalf;
    d_FFT[k + (N/2)].imag = imag2ndHalf;

    /*Orginal Version, doesnt Implement shared memory
    for( int n = 0; n < (N/2); n++)
    {
        // computes theta for even-index part of  d_timeDomain
        theta = (2 * M_PI * (2 * n) * k)/ N;

        // compute the DFT of even-indexed part of d_timeDomain, 
        // and accumulate it in real and imag
        real += (d_timeDomain[(2* n)].real * cos(theta)) +
                               (d_timeDomain[(2 * n)].imag *
                                                          sin(theta));
        imag += (-(d_timeDomain[(2*n)].real)* sin(theta)) + 
                               (d_timeDomain[(2 * n)].imag * 
                                                           cos(theta)); 

        // computes theta for even-index part of  d_timeDomain
        theta = (2 * M_PI * ((2 * n) + 1) * k)/ N;

        // compute the DFT of odd-indexed part of d_timeDomain, 
        // and accumulate it in real and imag
        real += (d_timeDomain[(2* n) + 1].real * cos(theta)) + 
                               (d_timeDomain[(2 * n) + 1].imag * 
                                                           sin(theta));
        imag += (-(d_timeDomain[(2*n) + 1].real)* sin(theta)) +  
                               (d_timeDomain[(2 * n) + 1].imag *
                                                          cos(theta)); 
    
        theta2ndHalf = (2 * M_PI * (2 * n) * (k+(N/2)))/ N;

        real2ndHalf += (d_timeDomain[(2 * n)].real *
                           cos(theta2ndHalf)) +
                            (d_timeDomain[(2 * n)].imag *
                                            sin(theta2ndHalf));

        imag2ndHalf +=  (-(d_timeDomain[(2 * n)].real)*
                               sin(theta2ndHalf)) + 
                                    (d_timeDomain[(2 * n)].imag
                                          * cos(theta2ndHalf)); 

        theta2ndHalf = (2 * M_PI * (n+ ((2 * n) + 1) *
                                                   (k+(N/2))))/ N;

        real2ndHalf += (d_timeDomain[((2 * n) + 1)].real * 
                                 cos(theta2ndHalf)) +
                                    (d_timeDomain[((2 * n) + 1)].imag 
                                                   * sin(theta2ndHalf));

        imag2ndHalf +=  (-(d_timeDomain[((2 * n) + 1)].real)* 
                         sin(theta2ndHalf)) + 
                          (d_timeDomain[((2 * n) + 1)].imag *
                                                  cos(theta2ndHalf)); 
    }

    // store result at appropriate location
    d_FFT[k].real = real;
    d_FFT[k].imag = imag;

    d_FFT[k + (N/2)].real = real2ndHalf;
    d_FFT[k + (N/2)].imag = imag2ndHalf;*/
}
