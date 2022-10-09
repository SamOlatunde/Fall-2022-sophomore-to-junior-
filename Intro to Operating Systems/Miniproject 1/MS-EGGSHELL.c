// Name: Samuel Olatunde
// Course: Introduction To Operating Systems - Fall 2022 
// Instructor: Nelson Passos
// Description: 
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int input = 0;

    printf("Please enter a number: ");
    scanf("%d", &input);

    int id = fork();

    if(id != 0)
    {
        fork();
    }

   

    return 0;
}