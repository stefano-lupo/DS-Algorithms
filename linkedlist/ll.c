#include <stdio.h>
#include <stdlib.h>

// Typedef it first so dont need "struct Node" everywhere
typedef struct Node Node; 

// Then do struct definition
struct Node {
    Node* next;
    int data;
};

// Let head be global
Node* head = NULL;

// Function declarations
void printLinkedList();
void addNode(int data);
Node* getLastNode();
Node* searchForNode(int data);
void addNodeToStart(int data);
void addNodeAfterData(int searchData, int newNodeAfterData);
void reverseLinkedList();

int main(){

    head = (Node*)malloc(sizeof(Node));
    head -> next = NULL;
    head -> data = 0;

    printLinkedList();
    addNode(15);
    printLinkedList();

    Node* searched = searchForNode(15);
    if(searched != NULL){
        printf("Node found: %d\n",searched->data);
    } else {
        printf("Node not contained in list\n");
    }

    addNodeToStart(99);
    printLinkedList();

    addNodeAfterData(0,100);
    addNodeAfterData(0,55);
    addNode(12);
    printLinkedList();

    reverseLinkedList();

    printLinkedList();
    return 0;
}

void printLinkedList(){
    Node* current = head;
    while(current != NULL){
        printf("%d ->",current->data);
        current = current->next;
    }
    printf("\n");
}

void addNode(int data){
    Node* last = getLastNode();
    Node* newLast = (Node*)malloc(sizeof(Node));
    newLast->data = data;
    newLast->next = NULL;
    last->next = newLast;
}

void addNodeToStart(int data){
    Node* newHead = (Node*)malloc(sizeof(Node));
    newHead->data = data;
    newHead->next = head;
    head = newHead;
}

Node* getLastNode(){
    Node* current = head;
    while(current->next != NULL){
        current = current->next;
    }
    return current;
}

Node* searchForNode(int data){
    Node* tmp = head;
    while(tmp->data != data){
        if(tmp->next != NULL){
            tmp = tmp->next;
        } else {
            return NULL;
        }
    }
    return tmp;
}

void addNodeAfterData(int searchData, int newNodeData){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newNodeData;

    Node* nodeAfter = NULL;
    Node* nodeBefore = head;

    while(nodeBefore != NULL){
        if(nodeBefore->data == searchData){
            nodeAfter = nodeBefore->next;
            nodeBefore->next = newNode;
            newNode->next = nodeAfter;
            return;
        } else {
            nodeBefore = nodeBefore->next;
        }
    }
    printf("That node with data %d is not contained in the list\n",searchData);

}

void reverseLinkedList(){
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;

//  while not at the end of the list
    while(current->next != NULL){
        Node* next = current->next; 
       
        current->next = prev;  

        // move all of our 3 pointers across one
        prev = current;
      
        current = next;
          
        next = next->next;
    }

    // once loop finished we have reached end of the list
    // need to make last node (which pointed to null to break loop)
    // point to second last node
    current->next = prev;

    // Set new head of list
    head = current;

}