#include <stdlib.h>
#include <stdio.h>

// Function prototypes
void printArray(int* arr);
void swap(int* arr, int index1, int index2);
void insertionSort(int* arr);


#define size 5

int arr[size] = {4,1,3,2,5};


int main(){
    printArray(arr);
    insertionSort(arr);
    printArray(arr);
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

void insertionSort(int* arr){
    // Iterate over array
    for(int i=0;i<size-1;i++){

        // Iterate backwards starting from the right adjacent
        for(int j=i+1;j>0;j--){
            // If current is smaller than one to its left
            if(arr[j]<arr[j-1]){
                swap(arr,j,j-1);
            } 
            
            // Otherwise break as left side of list is already sorted
            // so definitely not smaller than anything else to the left
            else {
                break;
            }
        }
    }
}