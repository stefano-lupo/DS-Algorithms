#include <stdio.h>
#include <stdlib.h>


// Function prototypes
void printArray(int* arr);
void swap(int* arr, int index1, int index2);
int bubbleSort(int* arr);

#define size 5

int arr[size] = {3,2,5,4,1};
int almostSorted[size] = {1,2,3,3,0};

int main(){
    int numIterations = bubbleSort(arr);
    printArray(arr);
    printf("Num iterations = %d\n",numIterations);

    // printArray(almostSorted);
    // numIterations = bubbleSort(almostSorted);
    // printArray(almostSorted);
    // printf("Num iterations = %d\n",numIterations);
    return 0;
}


void printArray(int* arr){
    printf("(");
    for(int i=0;i<size;i++){
        printf("%d, ",arr[i]);
    }
    printf(")\n");
}


void swap(int* arr, int index1, int index2){
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

int bubbleSort(int* arr){
    int numIterations = 0;
    int sorted = 0;

    while(sorted == 0){
        printArray(arr);
        numIterations++;
        sorted = 1;     // try break out on current pass
        for(int i=0;i<size-1;i++){
            numIterations++;
            if(arr[i+1] < arr[i]){
                swap(arr,i,i+1);
                sorted = 0;
            }
        }
    }

    return numIterations;
}