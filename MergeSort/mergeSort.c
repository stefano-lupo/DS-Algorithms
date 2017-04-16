#include <stdio.h>
#include <stdlib.h>



#define size 5

int arr[size] = {1,3,7,2,9};

void merge(int *arr, int first, int last);
void mergeSort(int *arr, int first, int last);
void printArray(int *arr);

int main(){
    printArray(arr);
    //mergeSort(arr,0,3);
    merge(arr,0,4);
    printArray(arr);

    return 0;
}


void mergeSort(int* arr, int first, int last){
    printf("First = %i, last = %i\n",first,last);
    // Recursion break
    if(first >= last){
        return;
    }

    int mid = (first+last)/2;
    //Recurse on left
    mergeSort(arr, first, mid);
    // Recurse on right
    mergeSort(arr,mid+1,last);
    printf("Merging first = %i and last = %i\n",first,last);
    merge(arr,first,last);
    printf("finished merging\n\n");
   
}


// Merge is capable of combining two sorted list into one sorted list
// key aspect is that lists with one element are sorted
// So give merge two lists each with one element
void merge(int *arr, int first, int last){
    // create resulting array (freed automatically on out of scope)
    int* result = alloca(sizeof(int)*(last-first));

    // [0,1, ... , 5,   6,7,...,n]
    //  first ..  mid   right .. end

    int midIndex = (last-first)/2;
    int left = first;
    
    int right = midIndex+1;
    int end = last;

    // where to start writing to array
    int outputIndex = first;

    while((left <=midIndex) && (right<=end)){
        printf("left[%d] = %d, right[%d] = %d  - ",left,arr[left],right,arr[right]);
        if(arr[left] < arr[right]){
            // putting in left
            printf("Taking left\n");
            result[outputIndex++] = arr[left++];
        } else {
            printf("Taking right\n");
            // putting in right (if equal also)
            result[outputIndex++] = arr[right++];
        }
    }

    // Check if anything was left in left list
    while(left<=midIndex){
        result[outputIndex++] = arr[left++];
    }

    // Check if anything was left in right list
    while(right <= end){
        result[outputIndex++] = arr[right++];
    }

    // Overwrite our array
    for(int i=first;i<=last;i++){
        printf("writing back %d = %i\n",i,result[i]);
        arr[i] = result[i];
    }

}

void printArray(int* arr){
    printf("(");
    for(int i=0;i<size;i++){
        printf("%d, ",arr[i]);
    }
    printf(")\n");
}