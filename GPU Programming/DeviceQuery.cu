#include<stdio.h>
#include<cuda.h>


int main()
{
    
   int dev_count;
   cudaGetDeviceCount(&dev_count);
    
   cudaDeviceProp dev_prop;
   for (int i =0; i < dev_count; i++)
   {
     cudaGetDeviceProperties(&dev_prop, i);
     printf("%d:  %d\n", i, dev_prop.sharedMemPerBlock);
   }
   
   printf("%u", sizeof(float));



    return 0;
}