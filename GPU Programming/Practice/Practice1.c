// Samuel Olatunde
// Practice based on Dr.C recomdenations in traditional C
#include <stdio.h>
#include <stdlib.h>

#define N 1024

int linearSearch(int a[], int key);
int binarySearch(int a[], int key);
void addArraysWithProcessingWindow(int a[], int b[], int c[], int size);
int main() {
    int* a = (int*)malloc(N * sizeof(int));
    int* b = (int*)malloc(N * sizeof(int));
    int* c = (int*)malloc(N * sizeof(int));
    int* testanswer = (int*)calloc(N, sizeof(int));



    // printf("%p\n", testanswer);
    //
    // initialize a
    for (int i = 0; i < N; i++) {

        a[i] = (2 * i);
        // printf(" %ld\n", a[i]);
    }

    ////initialize b
    for (int i = 0; i < N; i++) {
        b[i] = ((2 * i) + 1);
    }

    //// initialize test answer
    for (int i = 0; i < N; i++) {
        *(testanswer + i) = (2 * i) + ((2 * i) + 1);
    }

    // test run for linear and binary search
    /*int linear = linearSearch(a, 6);
    int binary = binarySearch(a, 6);

    printf("%d\n", linear);
    printf("%d\n", binary);*/

    addArraysWithProcessingWindow(a, b, c, 5);

    /*printf("c[1023] %ld\n", c[1023]);*/
    // for (int i = 0; i < N; i++)
    //{
    //    printf("%d \n", (c[i]));
    //    //printf("%d ", testanswer[i]);

    //}

    int correct = 0;
    for (int i = 0; i < N; i++) {
        correct = 0;

        if (testanswer[i] == c[i]) {
            correct = 1;
        }
    }

    printf("correct:%d", correct);

     free(a);
     free(b);
     free(c);
     free(testanswer);

    return 0;
}

int linearSearch(int a[], int key) {

    for (int i = 0; i < N; i++) {
        if (a[i] == key) {
            return i;
        }
    }

    return -1;
}

int binarySearch(int a[], int key) {
    int first = 0, last = N - 1;
    int mid;

    while (first <= last) {
        mid = (first + last) / 2;

        if (a[mid] == key) {
            return mid;
        }
        else if (key < a[mid]) {
            last = mid - 1;
        }
        else {
            first = mid + 1;
        }
    }

    return -1;
}

void addArraysWithProcessingWindow(int a[], int b[], int c[], int size) {
    for (int i = 0; i < N; i += 32) {
        //printf("%d\n", i);
        for (int j = i; j < i + 32; j++) {
           // printf("a: %ld\n", a[j]);
            //printf("b: %ld\n\n", b[j]);
            c[j] = a[j] + b[j];
           // printf("c: %ld\n\n\n", c[j]);
        }
    }
}