#include <stdio.h>
#include <stdlib.h>

#define size 6

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



int main(){
    // int arr[size] = {66, 55, 44, 33, 22, 11};
    // printArray(arr);
    // quicksort(arr,0,size-1);
    // printArray(arr);

    // printf("\n\n\n");
    // int arr2[size] = {66, 44, 33, 55, 11, 22};
    // printArray(arr2);
    // quicksort(arr2, 0, size-1);
    // printArray(arr2);
    

    printf("\n\n\n---------------\nRandom\n---------------\n");
    int random[size] = {44, 33, 55, 11, 00, 22};
    printArray(random);
    quicksort(random,0,size-1);
    printArray(random);

    printf("\n\n\n---------------\nWith Duplicates\n---------------\n");
    int withDupes[size] = {33, 33, 22, 11, 11, 44};
    printArray(withDupes);
    quicksort(withDupes, 0, size-1);
    printArray(withDupes);

    printf("\n\n\n---------------\nAscending\n---------------\n");
    int asc[size] = {00, 11, 22, 33, 44, 55};
    printArray(asc);
    quicksort(asc, 0, size-1);
    printArray(asc);

    printf("\n\n\n---------------\nDescending\n---------------\n");
    int desc[size] = {55, 44, 33, 22, 11, 00};
    printArray(desc);
    quicksort(desc, 0, size-1);
    printArray(desc);

    printf("\n\n\n---------------\nUniform\n---------------\n");
    int uni[size] = {33, 33, 33, 33, 33, 33};
    printArray(uni);
    quicksort(uni, 0, size-1);
    printArray(uni);

    return 0;
}

void quicksort(int *arr, int start, int end){

    if(start >= end){
        printf("Start of %d was >= than end of %d - returning\n\n", start, end);
        return;
    }

    int pivot = end;
    int wall = start;
    int currentIndex = start;
    printf("\n");
    printSubArray(arr,start,end);
    printf("Quicksorting: pivot of %i at %i (%d from the full array)\n", arr[pivot], pivot-start, pivot);

    for(currentIndex;currentIndex<end;currentIndex++){
        if(arr[currentIndex] < arr[pivot]){
            printf("%d (%d) is less than pivot of %d (%d) - swapping it with wall %d (at %d) and advancing wall to %d\n", 
                arr[currentIndex], currentIndex - start, arr[pivot], pivot-start, arr[wall], wall-start, wall-start+1);
            // put it to left of the wall
            // swap with element to right of the wall
            swap(arr,wall,currentIndex);
            wall++;
        } else {
            printf("%d (%d) is not less than %d (%d) - nothing to do on this iteration\n", arr[currentIndex], currentIndex - start, arr[pivot], pivot-start);
        }
    }

    printSubArray(arr,start,end);
    printf("Wall finished at %i (value = %d) or %d from the full array\n",wall-start, arr[wall], wall);
    printf("Swapping pivot of %d (at %d) with wall of %d (at %d)\n", arr[pivot], pivot-start, arr[wall], wall-start);
    swap(arr,pivot,wall);
    
    printSubArray(arr,start,end);
    printf("\n");
    
    quicksort(arr,start,wall-1);
    quicksort(arr,wall+1,end);

}