#include <stdio.h>
#include <stdlib.h>

/**
 * - Note this implementation is slightly tricker in some cases than the ll.c implementation
 * - This implementation does not store that head in a global variable 
 *   meaning it must be passed to all of the functions directly
 * - This isn't a big deal for most functions, but requires a double pointer
 *   for any functions which have to _change the head pointer_ 
 *     - E.g. adding a node to the start of the linked list
 *     - Reversing the linked list.
 * - https://github.com/stefano-lupo/c-cpp-grind/blob/master/c/pointers.c#L37-L83 contains some notes on why
 *   we need double pointers in some cases.
 */

// Typedef it first so dont need "struct Node" everywhere
typedef struct Node Node; 

// Then do struct definition
struct Node {
    int data;
    Node* next;
};


// Function declarations
void printNodeWithAddress(Node* node);
void printLinkedList(Node* head);
void addNodeToTail(Node* head, int data);
void addNodeToStart(Node** pointerToCallersHeadPointer, int data);      // Needs to be a Node** as it must mutate the head
Node* getLastNode(Node* head);
Node* searchForData(Node* head, int data);
void addNodeAfterData(Node* head, int searchData, int newNodeAfterData);
void reverseLinkedList(Node** pointerToCallersHeadPointer);             // Needs to be a Node** as it must mutate the head

int main(){
    
    // Create the head of the list
    Node* head = (Node*) malloc(sizeof(Node));
    head -> next = NULL;
    head -> data = 0;
    // printNodeWithAddress(head);

    printLinkedList(head);
    addNodeToTail(head, 15);
    addNodeToTail(head, 16);
    addNodeToTail(head, 17);
    printLinkedList(head);
    // printNodeWithAddress(head);


    // Adding a node to start by definition must be able to mutate our view of the linked list
    // Thus it must be able to change _our_ head pointer
    // Thus we pass a _pointer_ to our head pointer so that it can change it for us.
    // Thats where the double pointer comes from.
    addNodeToStart(&head, 19);
    printLinkedList(head);

    Node* searched = searchForData(head, 16);

    if(searched != NULL){
        printf("Node found: %d\n", searched->data);
    } else {
        printf("Node not contained in list\n");
    }

    addNodeAfterData(head, 16, 3);
    addNodeAfterData(head, 0, 55);
    addNodeToTail(head, 12);
    printLinkedList(head);

    // Try add node after 99 which is not in the list
    addNodeAfterData(head, 99, 3);

    reverseLinkedList(&head);

    printLinkedList(head);
    return 0;
}

void printNodeWithAddress(Node* node) {
    printf("The node pointer points to: %p\n", node);
    printf("[%p] Data: %d\n", &(node->data), node->data);
    printf("[%p] Next: %p\n", &(node->next), node->next);
}

void printLinkedList(Node* head){
    Node* current = head;
    while(current != NULL){
        printf("%d ->", current->data);
        current = current->next;
    }
    printf("\n");
}

void addNodeToTail(Node* head, int data){
    Node* last = getLastNode(head);

    // Create a brand new node that will become the tail
    Node* newLast = (Node*)malloc(sizeof(Node));
    newLast->data = data;
    newLast->next = NULL;
    
    // Connect the new node to the previous last nodes next
    last->next = newLast;
}

// This must take a pointer to a pointer as we want to change
// the what the CALLER's pointer is pointing to
// See this for an explanation https://github.com/stefano-lupo/c-cpp-grind/blob/master/c/pointers.c#L37-L83
void addNodeToStart(Node** pointerToCallersHeadPointer, int data){
    
    // Create the new head node and link it to the hold head
    Node* newHead = (Node*)malloc(sizeof(Node));
    newHead->data = data;
    newHead->next = *pointerToCallersHeadPointer;
    
    // Now get the _caller's_ pointer to the head by dereferencing 
    // the pointer we were given to the _caller's_ head pointer
    // and set that equal to the memory address of the new head
    *pointerToCallersHeadPointer = newHead;
}

Node* searchForData(Node* head, int data) {
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

Node* getLastNode(Node* head){
    Node* current = head;

    while(current->next != NULL){
        // We know that we're not at the end of the list as the node's _next_ is not NULL
        current = current->next;
    }

    return current;
}

void addNodeAfterData(Node* head, int searchData, int newNodeData){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newNodeData;


    Node* nodeAfter = NULL;
    Node* nodeBefore = head;

    while(nodeBefore != NULL){
        if(nodeBefore->data == searchData){
            // Get the next node, regardless of what it is (whether its an actual node or if its null)
            // as we need to connect newNode to it before we can free 
            nodeAfter = nodeBefore->next;

            nodeBefore->next = newNode;
            newNode->next = nodeAfter;

            return;
        }
        
        nodeBefore = nodeBefore->next;
    }

    // Wen't through entire list and didn't find the search data
    printf("That node with data %d is not contained in the list\n",searchData);
}

// This needs to be a double pointer so that we can make the caller's head become the tail.
void reverseLinkedList(Node** pointerToCallersHeadPointer){
    Node* prev = NULL;
    Node* current = *pointerToCallersHeadPointer;
    Node* next = NULL;

//  while not at the end of the list
    while(current->next != NULL){
        // Keep track of the next node before we change current's next
        Node* next = current->next; 
       
        // Now swap current's next to be the previouos node
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

    // Finally update the callers head pointer to be the previous tail
    *pointerToCallersHeadPointer = current;
}