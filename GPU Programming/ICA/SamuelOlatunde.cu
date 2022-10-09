// Samuel Olatunde 
// GPU Programming 
// ICA 1
#include<stdio.h>
#include<cuda.h>

// prototypes 
__global__
void arrPoduct1(int *d_A, int * d_B, int * d_C, int n);

__global__
void arrProduct2(int *d_A, int * d_B, int * d_C, int n);

int main()
{
    // variable and constant declarations 
    const int N = 10240;

    int A[N], B[N], C[N];
    int *d_A, * d_B, * d_C;
    int size = N * sizeof(int);

    // loop to initialize A with approprate values 
    for (int i = 0; i < N; i++)
    {
        A[i] = 2 * i;
    }
      
      

    // loop to initialize B with approprate values 
    for (int i = 0; i < N; i++)
    {
        B[i] = (2 * i) +1;
    }
    
    
    cudaMalloc((void**) &d_A, size);
    cudaMemcpy(d_A, A, size,cudaMemcpyHostToDevice);

    cudaMalloc((void**) &d_B, size);
    cudaMemcpy(d_B, B, size,cudaMemcpyHostToDevice);

    cudaMalloc((void**) &d_C, size);

    dim3 dimGrid( 2, 1, 1);
    dim3 dimBlock(1024 , 1, 1);
    
    // First Kernel Launch
    arrPoduct1<<<dimGrid, dimBlock>>>(d_A,d_B,d_C, N);
    
    cudaMemcpy(C, d_C, size,cudaMemcpyDeviceToHost);

    printf("2  Blocks (first, last) = ("); 
    printf("%d ", C[0]);
    printf(", ");
    printf("%d", C[N-1]);
    printf(")\n");

    dim3 dimGrid1( 10, 1, 1);
    dim3 dimBlock1(1024 , 1, 1);

    // Second KErnel Launch
    arrProduct2<<<dimGrid1, dimBlock1>>> (d_A, d_B, d_C, N);

    cudaMemcpy(C, d_C, size, cudaMemcpyDeviceToHost);
    
    printf("10 Blocks (first, last) = ("); 
    printf("%d ", C[0]);
    printf(", ");
    printf("%d", C[N-1]);
    printf(")\n");

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    
    return 0;
}


// This function uses threads to compute the product of two 
// arrays and places the result in a third array 
__global__
void arrPoduct1(int * d_A, int * d_B, int * d_C, int n)
{
    // maps local index to global index
   int i = blockDim.x * blockIdx.x + threadIdx.x;

   // computes the product
   if (i < n) d_C[i] = d_A[i] * d_B[i];
}

// This function uses threads to compute the product of two 
// arrays and places the result in a third array 
__global__
void arrProduct2(int *d_A, int * d_B, int * d_C, int n)
{
   int i = blockDim.x * blockIdx.x + threadIdx.x;

   if (i < n) d_C[i] = d_A[i] * d_B[i];
}