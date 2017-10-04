# Data Structures and Algorithms in C
This repository contains an implementation of some basic data structures and algorithms written in C. 
  
## Linked Lists
Linked Lists are a basic data structure in which each element in the list contains some data 
(may be a struct allowing for arbitrary data to be stored) and a pointer to the next element.  
This allows elements to be added to the list dynamically with ease which is beneficial over an array when the number of elements required is not known at compile time. 
  
However arrays are usually superior to linked lists when efficiency is required. Array lookup is constant time **O(1)** whereas linked lists require iteration through the entire list until an element is found and are thus linear time **O(n)**. Arrays are stored in contiguous blocks of memory and thus benefit strongly from caching whereas linked lists may be scattered throughout memory.
  
The following linked list functions are implemented:
  - void printLinkedList();
  - void addNode(int data);
  - Node* getLastNode();
  - Node* searchForNode(int data);
  - void addNodeToStart(int data);
  - void addNodeAfterData(int searchData, int newNodeAfterData);
  - void reverseLinkedList();
  
  
## Sorting
A variety of sorting algorithms can also be found in this repository and are split into the following two categories.
### Elementary
The following elementary sorts are implemented
  
1 Bubble   
2 Insertion   
3 Selection   

All of the implemented elementary sorts perform similarly and have are quadratic-time **O(n^2)** for the worst case. It is worth noting however that both bubble and insertion sort will stop after one pass **O(1)** on pre-sorted data. Selection sort on the other hand will always require a nested for loop and thus is always **O(n^2)**.
  
### Advanced Sorts
The following advanced sorting algorithms are also implemented.
The following elementary sorts are implemented:   
1 QuickSort   
2 MergeSort      
  
# Binary Search Tree

# Graphs
## Basic Graph Traversal
## Dijkstra's Algorithm
  
