#include <stdio.h>

#define size 50

int main() {

        // Value we want
        int searchingFor = 15;

        // Keep track of start and end of our sublists
        int startIndex = 0;
        int endIndex = size - 1; // dont miss the -1

        // Create and fill array
        int arr[size];
        for (int i = 0; i < size; i++) {
            arr[i] = i;
        }

        int found = 0;
        int middle;

        while (1){
            if (endIndex < startIndex){
                break;
            }

            // split list
            middle = ((endIndex - startIndex) / 2) + startIndex; // int division rounds down

            if (arr[middle] == searchingFor){
                found = 1;
                break;
            }

            else if (arr[middle] < searchingFor){
                startIndex = middle + 1;
            }

            else{
                endIndex = middle - 1;
            }
        }

        if (found == 1){
            printf("Found %d at index %d\n", searchingFor, middle);
        }
        else{
            printf("%d is not in the array\n", searchingFor);
        }
    return 0;
}