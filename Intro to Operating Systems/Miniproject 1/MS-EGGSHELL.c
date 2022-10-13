// Name: Samuel Olatunde
// Course: Introduction To Operating Systems - Fall 2022 
// Instructor: Nelson Passos
// Description: This program makes use of the system call fork(),
// to make 3 processes which each run lseek to change the location 
// of the read/write pointer to a file. The program takes integer 
// input from the user (without prompt), which represents the byte
// location the first process starts reading from. The next two
// processes to run add 10, 20 respectively to the user input then 
// starts reading from the new position.
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main()
{
    // variable declarations
    int input = 0, fd, fd2, id, position;
    char buf[5];

    // read user input from keyboard 
    scanf("%d", &input);

    fd = open("MS-EGGSHELL.c", O_RDONLY);

    id = fork();

    // if the process is not a child,
    // create another process
    if (id != 0)
    {
        // call to create a duplicate process
        id = fork();

        // this set of conditionals help to specify the 
        // number of bytes we are skiping with each lseek call.
        // So all processes dont read from the same position.
        if (id != 0)
        {
            input += 10;
        }
        else
        {
            input += 20;
        }
    }

    lseek(fd, input, SEEK_SET);

    // read characters and place it in the buffer
    read(fd, buf, 5);

    // print content of buffer on the screen (or the file in this case)
    write(1, buf, 5);
    write(1, " ", 1);

    return 0;
}