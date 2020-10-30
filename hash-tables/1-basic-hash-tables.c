#include <stdio.h>
#include <stdlib.h>

// Needed for strcpy
#include <string.h>


// How big our hash table is
#define ARRAY_SIZE 23

// How long the longest surname we will support is
#define MAX_NAME_LENGTH 20

typedef struct NameCount {
  int occurences;
  char* name;
} NameCount;

NameCount* hashTable[ARRAY_SIZE];


/** The basic hash function 
 * modding by the array size at the end ensures it will always land
 * within the bounds of our array that we're using as a hash table
 * */
int hash(char* s) {
  int hash = 0;
  while (*s) {
    hash = hash + *s;
    s++;
  }

  return hash % ARRAY_SIZE;
}

void printHashOf(char* s) {
  printf("%s --> %i\n", s, hash(s));
}

void printHashTable() {
  printf("\n------- Full Hash Table ------ \n");
  for (int i=0; i<ARRAY_SIZE; i++) {
    NameCount* nameCount = hashTable[i];
    if (nameCount != NULL) {
      printf("%d --> %s:%d\n", i, nameCount -> name, nameCount -> occurences);
    }
  }
}

void insertIntoHashTableOverwritingCollisions(char* name) {
  int index = hash(name);

  NameCount* nameCount = (NameCount*) malloc(sizeof(NameCount));
  nameCount -> name = name;
  nameCount -> occurences = 1;

  hashTable[index] = nameCount;
}


int main() {
  char jones[MAX_NAME_LENGTH] = "Jones";
  char floyd[MAX_NAME_LENGTH] = "Floyd";
  insertIntoHashTableOverwritingCollisions(jones);
  insertIntoHashTableOverwritingCollisions(floyd);
  printHashTable();
  
  char dyolf[MAX_NAME_LENGTH] = "dyolF";    // Just floyd backwards, will collide with floyd.  printHashOf(jones);
  insertIntoHashTableOverwritingCollisions(dyolf);

  printHashTable();
}