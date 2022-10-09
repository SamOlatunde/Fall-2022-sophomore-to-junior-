//*****************************************************************
//                   Assignment #3
//                    Names: Samuel Olatunde 
//                    GPU PRogramming
//                    Date: 10/05/2022
//*****************************************************************
//   This is a cuda c program that implements uses 
//   3 kernels calculate the product of two same size arrays, A
//   and B, then stores the result in a third array C
//*****************************************************************
#include<stdio.h>
#include<cuda.h>

// Kernel Prototypes 
__global__ 
void notCyclicArrProduct1(int * d_A, int * d_B, int * d_C, int N);
__global__
void cyclicArrProduct1(int * d_A, int * d_B, int * d_C, int N);
__global__
void arrProduct2(int * d_A, int * d_B, int * d_C);

int main()
{
    // Constant/variable declaration/initializations 
    const int N = 10240;
    int A[N],B[N],C[N];
    int * d_A, * d_B, * d_C;
    int size = N * sizeof(int);

    // Initializes array A with even sequence (2n)
    for (int i = 0; i < N; i++)
    {
        A[i] = 2 * i;
    }

    // Initializes array B with odd sequence (2n+1)
    for (int i = 0; i < N; i++)
    {
        B[i] = (2* i) + 1;
    }
    
    // allocates memory for A in the global memory, saves the
    // address in device variable d_A and transfers data from
    // main memory to global memory
    cudaMalloc((void**) &d_A, size);
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);
    
    // allocates memory for B in the global memory, saves the
    // address in device variable d_B and transfers data from
    // main memory to global memory
    cudaMalloc((void **) &d_B, size);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // allocates memory for C in the global memory, saves the
    // address in device variable d_A 
    cudaMalloc((void **) &d_C, size);
    
    // grid and block dimension specifications
    dim3 dimGrid(2,1,1);
    dim3 dimBlock(1024,1,1);

    // Kernel Launched with 2 blocks of 1024 threads each 
    notCyclicArrProduct1<<<dimGrid,dimBlock>>>(d_A,d_B,d_C, N);
    
    // copies data for C from global memory to main memory
    cudaMemcpy(C,d_C, size, cudaMemcpyDeviceToHost);
    
    // frees up global memory 
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // output statment 
    printf("2 Blocks - Not Cyclic ( C[0], C[10239] ) = (");
    printf("%d", C[0]);
    printf(", ");
    printf("%d", C[10239]);
    printf(")\n");
    
    // allocates memory for A in the global memory, saves the
    // address in device variable d_A and transfers data from
    // main memory to global memory
    cudaMalloc((void**) & d_A, size);
    cudaMemcpy(d_A,A,size, cudaMemcpyHostToDevice);

    // allocates memory for B in the global memory, saves the
    // address in device variable d_B and transfers data from
    // main memory to global memory
    cudaMalloc((void**) & d_B, size);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);

    // allocates memory for C in the global memory, saves the
    // address in device variable d_C 
    cudaMalloc((void**) & d_C, size);
    
    // Kernel launched with 2 blocks of 1024 threads each 
    cyclicArrProduct1<<< dimGrid, dimBlock>>>(d_A,d_B,d_C,N);

    // copies data for C from global memory to main memory
    cudaMemcpy(C,d_C,size,cudaMemcpyDeviceToHost);

    // frees up global memory 
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    printf("2 Blocks - Cyclic ( C[0], C[10239] ) = (");
    printf("%d", C[0]);
    printf(", ");
    printf("%d", C[10239]);
    printf(")\n");

    // allocates memory for A in the global memory, saves the
    // address in device variable d_A and transfers data from
    // main memory to global memory
    cudaMalloc((void**) & d_A, size);
    cudaMemcpy(d_A, A, size, cudaMemcpyHostToDevice);

    // allocates memory for B in the global memory, saves the
    // address in device variable d_B and transfers data from
    // main memory to global memory
    cudaMalloc((void**) & d_B, size);
    cudaMemcpy(d_B, B, size, cudaMemcpyHostToDevice);
    
    // copies data for C from global memory to main memory
    cudaMalloc((void**) & d_C, size);
    
    // grid and block specifications 
    dim3 dimGrid1(10,1,1);
    dim3 dimBlock1(1024,1,1);
    
    // Kernel Launched with 10 blocks of 1024 threads each
    arrProduct2<<< dimGrid1, dimBlock1 >>> (d_A, d_B, d_C);
    
    // copies data for C from global memory to main memory
    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);

    // frees up global memory 
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);

    // output Statment 
    printf("10 Blocks -( C[0], C[10239] ) = (");
    printf("%d", C[0]);
    printf(", ");
    printf("%d", C[10239]);
    printf(")\n");

    return 0;
}


//********************************************************************
//                     Name:: notCyclicArrProduct1
//                    Parameters: 3 device pointers to arrays, 
//                                1 int for the size of each array 
//   This Kernel computes the product by noncyclic data partitioning 
//********************************************************************
__global__ 
void notCyclicArrProduct1(int * d_A, int * d_B, int * d_C, int N)
{
   int AmtOfDataPerThreadBlock = N / gridDim.x;
   int nonCyclicIndex;
   int AmtOfDataPerThread = AmtOfDataPerThreadBlock/ blockDim.x;

   for (int i = 0; i < AmtOfDataPerThread; i++)
   {
       nonCyclicIndex = (blockIdx.x * blockDim.x  * AmtOfDataPerThread 
                         + threadIdx.x) + (i * blockDim.x);

       d_C[nonCyclicIndex] = d_A[nonCyclicIndex] * d_B[nonCyclicIndex];
   }
}

//********************************************************************
//                     Name:: cyclicArrProduct1
//                    Parameters: 3 device pointers to arrays, 
//                                1 int for the size of each array 
//    This kernel computes the product by cyclic data partitioning, 
//    i.e. each thread block computes as many theadBlocks sized 
//    chunks of data as it needs to in order to process all data but 
//    in a cyclic manner. So if we had two thread blocks of size n 
///    and N data elements to process block 
//********************************************************************
__global__
void cyclicArrProduct1(int * d_A, int * d_B, int * d_C, int N)
{
   // local to global index mapping 
   int index = blockIdx.x * blockDim.x + threadIdx.x;

   // calculates the total number of threads in the grid 
   int totalThreads = gridDim.x * blockDim.x;
   int cyclicIndex; 

   // calculates the times we are reusing a thread
   int numberOfElementsPerThread = N/totalThreads;
 
   for (int i = 0; i < numberOfElementsPerThread; i++)
   {
     cyclicIndex = index + (i * totalThreads);

     d_C[cyclicIndex] = d_A[cyclicIndex] * d_B[cyclicIndex];
   }   
}

//********************************************************************
//                     Name:: notCyclicArrProduct1
//                    Parameters: 3 device pointers to arrays, 
//    This kernel is written with the assumption that it is launched 
//    with sufficent blocks and  threads the porcess all available
//    data                            
//********************************************************************
__global__
void arrProduct2(int * d_A, int * d_B, int * d_C)
{
    // maps local index of each thread to global index 
   int i = blockIdx.x * blockDim.x + threadIdx.x;
   
   // computes product
   d_C[i] = d_A[i] * d_B[i];
}

