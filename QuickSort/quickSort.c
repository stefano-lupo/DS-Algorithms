#include <stdio.h>
#include <stdlib.h>

#define size 4

void quicksort(int* arr, int start, int end);

void swap(int* arr, int i1, int i2){
    int temp = arr[i1];
    arr[i1] = arr[i2];
    arr[i2] = temp;
}

void printArray(int* arr){
    printf("(");
    for(int i=0;i<size;i++){
        printf("%d, ",arr[i]);
    }
    printf(")\n");
}
void printSubArray(int* arr, int start, int end){
    printf("(");
    for(int i=start;i<=end;i++){
        printf("%d, ",arr[i]);
    }
    printf(")\n");
}

int arr[size] = {4,3,2,1};

int main(){
    quicksort(arr,0,size-1);
    printArray(arr);

    return 0;
}

void quicksort(int *arr, int start, int end){

    if(start >= end){
        return;
    }

    int pivot = end;
    int wall = start;
    int currentIndex = start;
    printf("\n");
    printSubArray(arr,start,end);
    printf("Quicksorting: pivot = arr[%i] = %d\n",pivot,arr[pivot]);

    for(currentIndex;currentIndex<end;currentIndex++){
        if(arr[currentIndex] < arr[pivot]){
            printf("%d is less than %d \n",arr[currentIndex],arr[pivot]);
            // put it to left of the wall
            // swap with element to right of the wall
            swap(arr,wall,currentIndex);
            wall++;
        } 
    }

    swap(arr,pivot,wall);

    printf("Wall finished at %i\n",wall);
    printSubArray(arr,start,end);
    printf("\n");
    
    quicksort(arr,start,wall-1);
    quicksort(arr,wall+1,end);

}