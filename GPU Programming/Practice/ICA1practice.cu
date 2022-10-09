#include <stdio.h>
#include<cuda.h>
using namespace std;

// prototypes 
__global__
void vecAddKernel(float * d_A, float * d_B, float * d_C, int n);
void vecAdd(float * h_A, float * h_B, float * h_C, int n);


int main()
{
    int size = 5;
    float A[size] = {2,2,2,2,2}, B[size] = {2,2,2,2,2}, C[size];

    vecAdd(A,B,C, size);

    for (int i = 0; i < size; i++)
    {
        printf("%f\t", C[i]);
    }    

    return 0;
}

// Kernel fucntion, n is the numbe o f elements in each array
__global__
void vecAddKernel(float * d_A, float * d_B, float * d_C, int n)
{
    // mapping local index to global index 
    int i = blockDim.x * blockIdx.x + threadIdx.x;
     
    if (i < n) 
      d_C[i] = d_A[i] + d_B[i];

}


void vecAdd(float * h_A, float * h_B, float * h_C, int n)
{
    float *d_A,* d_B, *d_C;

    // calculates number of bytees needed to store the array
    int size = n * sizeof(float);

    // allocates memory for d_A in the global memory and transfers data from main memory to global memory
    cudaMalloc((void**) &d_A, size);
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

    // allocates memory for d_C in the global memory and transfers data from main memory to global memory
    cudaMalloc((void**) &d_B, size);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // allocates memory for d_C in the global memory 
    cudaMalloc((void**) & d_C, size);

    // specifies the grid dimensions
    dim3 dimGrid(1,1,1);

    // specifies block dimensions
    dim3 dimBlock(n,1,1);

    // kernel lauch statement 
    vecAddKernel<<<dimGrid,dimBlock>>>(d_A, d_B, d_C, n);
    

    // copys the answer back to main memory 
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // frees up global memory 
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);



}