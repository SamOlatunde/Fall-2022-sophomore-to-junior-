#include<stdio.h>
#include<cuda.h>

const int N = 7;

__global__
void helloWorld(char * a, int * b);

int main()
{
    char a[N] = "Hello ";
    int b[N] = {15,10,6,0,-11,1,0};
    

    char * ad;
    int * bd;
    const int csize = N * sizeof(char);
    const int isize = N * sizeof(int);
    
    printf("%s", a);

    cudaMalloc((void**) &ad, csize);
    cudaMalloc((void**) &bd, isize);

    cudaMemcpy(ad, a, csize, cudaMemcpyHostToDevice);
    cudaMemcpy(bd,b, isize, cudaMemcpyHostToDevice);

    dim3 dimGrid(1,1,1);
    dim3 dimBlock(N,1,1);

    helloWorld<<<dimGrid, dimBlock >>>(ad,bd);

    cudaMemcpy(a,ad,csize,cudaMemcpyDeviceToHost);
    cudaFree(ad);
    cudaFree(bd);

    printf("%s", a);

    return 0;
}

__global__
void helloWorld(char * a, int * b)
{
   int i = blockDim.x * blockIdx.x +threadIdx.x;
   if(i < N) a[i]+=b[i];
}
