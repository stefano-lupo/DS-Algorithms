#include <stdio.h>
#include <stdlib.h>



typedef struct Node Node;

struct Node {
    Node* left;
    Node* right;
    int data;
};

void insertNode(Node* currentNode, int data);
void printTree_InOrder(Node* currentNode);
void deleteTree(Node* currentNode);
Node* search(Node* currentNode, int data);

int mallocs = 0, frees = 0;

int main(){


    int numbers[] = {4,2,6,1,3,5,7};
    Node* root = (Node*)malloc(sizeof(Node));
    mallocs++;
    root->right = NULL;
    root->left = NULL;
    root->data = numbers[0];

    for(int i=1;i<sizeof(numbers)/sizeof(numbers[0]);i++){
        insertNode(root,numbers[i]);
    }


    printTree_InOrder(root);
    printf("\n\n");

    Node* searched = search(root,2);
    if(searched != NULL){
        printf("Search found %i\n",searched->data);
        if(searched->left!=NULL){
            printf("Left child = %i,",searched->left->data);
        }
        if(searched->right!=NULL){
            printf("Right child = %i,",searched->right->data);
        }
        printf("\n");
    }

    deleteTree(root);
    printf("Mallocs = %i, frees = %i\n\n",mallocs,frees);

    return 0;
}

void insertNode(Node* currentNode, int data){

    if(data < currentNode->data){
        // Go to the left
        if(currentNode->left == NULL){
            // Place it as left child if empty
            Node* newNode = (Node*)malloc(sizeof(Node));
            mallocs++;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->data = data;
            currentNode->left = newNode;
            return;
        } else {
            // Otherwise recurse down left sub tree
            insertNode(currentNode->left,data);
        }
    } else if(data > currentNode->data){
        // Go to the right
        if(currentNode->right == NULL){
            // Place it as right child if empty
            Node* newNode = (Node*)malloc(sizeof(Node));
            mallocs++;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->data = data;
            currentNode->right = newNode;
            return;
        } else {
            // Otherwise recurse down right sub tree
            insertNode(currentNode->right,data);
        }
    } else {
        // Data already in tree
        printf("%i is already in the tree\n\n",data);
    }
}

// Uses post order traversal
// Traverses down left tree until hits null (leaf node)
// Returns up one level, printf(leaf node data)
// Check its right child too
void printTree_InOrder(Node* currentNode){
    if(currentNode == NULL){
        return;
    }

    printTree_InOrder(currentNode->left);
    printf("%i ",currentNode->data);
    printTree_InOrder(currentNode->right);
}

// Uses post order traversal
void deleteTree(Node* currentNode){
    if(currentNode == NULL){
        return;
    }

    deleteTree(currentNode->left);
    deleteTree(currentNode->right);
    frees++;
    free(currentNode);
}

Node* search(Node* currentNode, int data){
    if(currentNode == NULL){
        return NULL;
    }


    if(data < currentNode->data){
       return search(currentNode->left,data);
    } 
    
    else if(data > currentNode->data){
       return search(currentNode->right,data);
    }

    else {
        return currentNode;
    }
}