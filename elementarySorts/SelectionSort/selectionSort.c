#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5


typedef struct Record {
    int age;
    char name[256];
} Record;




void printArray(Record** records);

// Recall arrays decay to pointers
void selectionSort(Record** records);

void swap(Record** records, int index1, int index2);

int main (){


    Record* records[SIZE];

    // Generate structs
    for(int i=0;i<SIZE;i++){
        records[i] = (Record*)malloc(sizeof(Record));
    }

    // Stable Search so Mac Denis Charlie order perserved
    strcpy(records[0]->name, "Stefano");
    strcpy(records[1]->name, "Frank");
    strcpy(records[2]->name, "Mac");
    strcpy(records[3]->name, "Denis");
    strcpy(records[4]->name, "Charlie");

    records[0]->age = 21;
    records[1]->age = 65;
    records[2]->age = 30;
    records[3]->age = 30;
    records[4]->age = 30;

    printArray(records);
    selectionSort(records);
    printArray(records);


}

void printArray(Record** records){
    printf("(");
    for(int i=0;i<SIZE;i++){
        printf("(%d,%s) - ",records[i]->age,records[i]->name);
    }
    printf(")\n");
}

void selectionSort(Record** records){
    int minIndex;

    /*************************************************************************
    i=0;i<SIZE;i++ for normal array obviously
    i=0;i<SIZE-1;i++ for searching to 2nd last element for first for loop
    **************************************************************************
    */
    for(int i=0;i<SIZE-1;i++){
        minIndex = i;
        for(int j=i+1;j<SIZE;j++){
            if(records[j]->age < records[minIndex]->age){
                minIndex = j;
            }
        }
        if(i != minIndex){
            swap(records,i,minIndex);
        }
    }
}

void swap(Record** records, int index1, int index2){
    Record* temp = records[index1];
    records[index1] = records[index2];
    records[index2] = temp;
}

