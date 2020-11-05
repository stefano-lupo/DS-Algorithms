#include <stdio.h>
#include <stdlib.h>

// Typedef it first so dont need "struct Node" everywhere
typedef struct Node Node; 

// Then do struct definition
struct Node {
    Node* next;
    int data;
};


/**
 * [ 0 ] --> [ 15 ] --> [ 16 ] --> [ 17 ] --> [ / ]
 *  ^
 *  | 
 *  current
 */
 


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
void removeNodeFromList(int data);


int main(){
    
    // Create the head of the list
    head = (Node*) malloc(sizeof(Node));
    head -> next = NULL;
    head -> data = 0;

    printLinkedList();
    addNode(15);
    addNode(16);
    addNode(17);
    printLinkedList();

    Node* searched = searchForNode(19);

    if(searched != NULL){
        printf("Node found: %d\n",searched->data);
    } else {
        printf("Node not contained in list\n");
    }

    // addNodeToStart(99);
    // printLinkedList();

    addNodeAfterData(16, 3);
    // addNodeAfterData(0,55);
    // addNode(12);
    printLinkedList();

    // Try add node after 99 which is not in the list
    addNodeAfterData(99, 3);

    // reverseLinkedList();

    // printLinkedList();
    // return 0;
}

void printLinkedList(){
    Node* current = head;
    while(current != NULL){
        printf("%d ->", current->data);
        current = current->next;
    }
    printf("\n");
}

void addNode(int data){
    Node* last = getLastNode();

    // Create a brand new node that will become the tail
    Node* newLast = (Node*)malloc(sizeof(Node));
    newLast->data = data;
    newLast->next = NULL;
    
    // Connect the new node to the previous last nodes next
    last->next = newLast;
}

Node* searchFor(int data) {
    Node* current = head;

    while(current != NULL) {
        
        printf("Checking %d\n", current -> data);
        if (current -> data == data) {
            // Found a match, so return this node.
            return current;
        }

        current = current -> next;
    }

    // At this point, we finished iterating through the list, but didn't find the data
    return NULL;
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
        // We know that we're not at the end of the list as the node's _next_ is not NULL
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
            // Get the next node, regardless of what it is (whethers its an actual node or if its null)
            // as we need to connect newNode to it 
            nodeAfter = nodeBefore->next;

            nodeBefore->next = newNode;
            newNode->next = nodeAfter;

            return;
        } else {
            nodeBefore = nodeBefore->next;
        }
    }

    // Wen't through entire list and didn't find the search data
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

void removeNodeFromList(int data) {
    // Handle case where data is found in first node
    if (head -> data == data) {
        
        Node* oldHead = head;
        head = head -> next;
        free(oldHead);
        return;
    }
    
    Node* current = head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current -> data == data) {           
            // Connect the previous node's next to the next node
            previous -> next = current->next;

            // We've found the element
            free(current);
            
            return;
        }

        // Move our two pointers down the list 1 spot
        previous = current;
        current = current -> next;
    }
}