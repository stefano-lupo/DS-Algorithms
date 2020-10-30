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


// Forward declare functions so we dont have to worry about their ordering 
int hash(char* s);
void printHashOf(char* s);
void printHashTable();
int isNameCountForName(NameCount* nameCount, char* name);
void createNameCountForNameAtIndex(char* name, int index);
void insertIntoHashTable(char* name);
void linearProbeInsert(char* name, int collisionIndex);
int getNumberOfOccurencesForName(char* name);
int linearProbeSearch(char* name, int collisionIndex) ;

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
  printf("\n\n------- Full Hash Table ------ \n");
  for (int i=0; i<ARRAY_SIZE; i++) {
    NameCount* nameCount = hashTable[i];
    if (nameCount != NULL) {
      printf("%d --> %s:%d\n", i, nameCount -> name, nameCount -> occurences);
    }
  }
  printf("-----------------------------------\n\n");
}


int isNameCountForName(NameCount* nameCount, char* name) {
  // If the names match, then this is the NameCount we should use for this name.
  if (strcmp(name, nameCount->name) == 0) {
    return 1;
  }

  return 0;
}

void createNameCountForNameAtIndex(char* name, int index) {
  NameCount* nameCount = (NameCount*) malloc(sizeof(NameCount));
  nameCount -> name = name;
  nameCount -> occurences = 1;

  hashTable[index] = nameCount;
}

void insertIntoHashTable(char* name) {
  int index = hash(name);

  // check the table to see if we already have a value at this index
  NameCount* nameCount = hashTable[index];
  if (nameCount == NULL) {
    // Nothing in the table at this index so just insert this one
    printf("No existing name count at index %d so inserting a new one for %s\n", index, name);
    createNameCountForNameAtIndex(name, index);
    return;
  } 

  // There is already something at this index.
  // If it matches the current name we're looking for, then we can just increment it's occurences
  // strcmp returns 0 if strings match
  int namesMatch = isNameCountForName(nameCount, name);
  if (namesMatch == 1) {
    // We found the relevant nameCount for this name, so just incremement it's occurences.
    nameCount -> occurences = nameCount -> occurences + 1;
    printf("Found existing nameCount at index %d for %s - incremented occurences to %d\n", index, name, nameCount -> occurences);
  } else {
    // We hit a collision
    linearProbeInsert(name, index);
  }
}

void linearProbeInsert(char* name, int collisionIndex) {
  printf("Hit collision for %s at %d, starting linear probing\n", name, collisionIndex);
  int indexToCheck = collisionIndex + 1;
  while (indexToCheck != collisionIndex) {
    if (indexToCheck == ARRAY_SIZE) {
      // Wrap around back to the start of the array
      indexToCheck = 0;
    }

    printf("Examining index %d for %s\n", indexToCheck, name);

    NameCount* nameCount = hashTable[indexToCheck];

    if (nameCount == NULL) {
      // We found an empty spot - this means that the name we're looking for is not in the hash table
      // create a new entry for it
      createNameCountForNameAtIndex(name, indexToCheck);
      printf("Found empty index %d for %s indicating it didn't exist in table - creating new NameCount for it\n", indexToCheck, name);
      return;
    }

    int matches = isNameCountForName(nameCount, name);
    if (matches == 1) {
      // We found the match so just increment this NameCount's occurences
      nameCount -> occurences = nameCount -> occurences + 1;
      printf("Found matched name count at %d for %s, incrementing occurences to %d\n", indexToCheck, name, nameCount -> occurences);
      return;
    }

    // The NameCount at this index is not for this name, continue with search
    indexToCheck ++;
  }

  // If we get to this point, we have completed the while loop which means
  // we have gotten to the point where indexToCheck is back to collisionIndex (where we started)
  // This means we searched the entire hash table and didn't find an existing NameCount for this name.
  // and we also didn't find an empty slot to insert into meaning the table is full.
  printf("The table is full and did not contain %s - cannot insert!\n", name);
}

int getNumberOfOccurencesForName(char* name) {
  int index = hash(name);

  NameCount* nameCount = hashTable[index];
  if (nameCount == NULL) {
    // name is definitely not in the table
    printf("Name %s is not in the hash table\n", name);
    return 0;
  }

  int matches = isNameCountForName(nameCount, name);
  if (matches) {
    printf("Found NameCount for %s at index %d and had %d collisions \n", name, index, nameCount->occurences);
    return nameCount -> occurences;
  }

  // We hit a collision and must linear probe search
  return linearProbeSearch(name, index);
}

int linearProbeSearch(char* name, int collisionIndex) {
  // Lots of duplicated code from linearProbeInsert that should probably be in a common function
  

  int indexToCheck = collisionIndex + 1;
  while (indexToCheck != collisionIndex) {
    if (indexToCheck == ARRAY_SIZE) {
      // Wrap around back to the start of the array
      indexToCheck = 0;
    }

    printf("Examining index %d for %s\n", indexToCheck, name);

    NameCount* nameCount = hashTable[indexToCheck];

    if (nameCount == NULL) {
      // We found an empty spot - this means that the name we're looking for is not in the hash table
      // Therefore there was no occurences of this name.
      printf("Found empty index %d for %s indicating it didn't exist in table\n", indexToCheck, name);
      return 0;
    }

    int matches = isNameCountForName(nameCount, name);
    if (matches == 1) {
      // We found the match so return the occurences of this NameCount
      printf("Found matched name count at %d for %s, returning occurences of %d\n", indexToCheck, name, nameCount -> occurences);
      return nameCount -> occurences;
    }

    // The NameCount at this index is not for this name, continue with search
    indexToCheck ++;
  }

  // If we get to this point, we have completed the while loop which means
  // we have gotten to the point where indexToCheck is back to collisionIndex (where we started)
  // This means we searched the entire hash table and didn't find an existing NameCount for this name.
  // and we also didn't find an empty slot meaning the table is full and didn't contain the name.
  printf("The table is full and did not contain %s - this means it had 0 occurences!\n", name);
  return 0;
}

int main() {
  char jones[MAX_NAME_LENGTH] = "Jones";
  char floyd[MAX_NAME_LENGTH] = "Floyd";
  char dyolf[MAX_NAME_LENGTH] = "dyolF";    // Just floyd backwards, will collide with floyd
  printHashOf(jones);
  printHashOf(floyd);
  printHashOf(dyolf);

  insertIntoHashTable(jones);
  insertIntoHashTable(floyd);
  printHashTable();
  
  // Insert a collision for testing.
  insertIntoHashTable(dyolf);
  printHashTable();

  // Insert a few more of jones to incrememnt the occurences
  insertIntoHashTable(jones);
  insertIntoHashTable(jones);
  insertIntoHashTable(jones);
  printHashTable();

  // Run searches
  int numJones = getNumberOfOccurencesForName(jones);
  printf("\nFound %d occurences of jones and was expecting 4\n\n", numJones);

  int numFloyd = getNumberOfOccurencesForName(floyd);
  printf("Found %d occurences of floyd and was expecting 1\n\n", numFloyd);

  int numDyolf = getNumberOfOccurencesForName(dyolf);
  printf("Found %d occurences of dyolf and was expecting 1\n\n", numDyolf);

  char farrell[MAX_NAME_LENGTH] = "Farrell";
  int numFarrell = getNumberOfOccurencesForName(farrell);
  printf("Found %d occurences of farrell and was expecting 0\n\n", numFarrell);
}