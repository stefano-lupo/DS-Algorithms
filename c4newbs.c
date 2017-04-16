#include <stdio.h>  // print
#include <stdlib.h> // malloc
#include <string.h> // c string functions (strcpy etc)


// Arrays - Need array size on declaration (not just initialization like java)
#define ARR_SIZE 5  // NO EQUALS OR SEMI COLON
// Array sizes go AFTER name!
int myArray[ARR_SIZE];
int myInitializedArray[ARR_SIZE] = {1,2,3,4,5};

// Typedefing structs
typedef struct Person {
    char name[256];
    int age;
} Person;              // Semi colon at end of structs

// pointer types are just for convenience


// Passing arrays to functions
// Really are passing a pointer to the first element in array
// As it has decayed to pointer, no info regarding array size
// Need to pass the size or have it global
// Can index pointes with array notation to access adjacent memory
// The following two are equivalent
double getAverage(int arr[], int size);  
double getAveragePointer(int* arrStart, int size);   

int main(){
    
    // Array length
    printf("Array length = %d\n", sizeof(myArray)/sizeof(myArray[0]));

    // Better off
    for(int i=0;i<ARR_SIZE;i++){
        printf("%d - %d\n",i,myInitializedArray[i]);
    }

    // initializing structs
    Person* me = (Person*)malloc(sizeof(Person));
    strcpy(me->name,"Stefano Lupo");
    me->age = 21;


    // Free memory and set pointer to null (good practice)
    me = NULL;
    free(me);


    // Using arrays as parameters
    double average = getAverage(myInitializedArray,ARR_SIZE);
    printf("Average = %f\n",average);

    // 
    average = getAveragePointer(myInitializedArray,ARR_SIZE);
    printf("Average = %f\n",average);

    return 0;
}


double getAverage(int arr[], int size){
    double average = 0;
    for(int i=0;i<size;i++){
        average += arr[i];
    }
    return average/size;
}

double getAveragePointer(int *arrStart, int size){
    double average = 0;
    for(int i=0;i<size;i++){
        average += arrStart[i];
    }
    return average/size;
}