#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex Vertex;

struct Vertex{
    char data;
    LinkedListNode* edges;
};

typedef struct Edge Edge;

struct Edge {
    Vertex* connectedTo;
    int weight;
};


typedef struct LinkedListNode;

struct LinkedListNode {
    LinkedListNode* next;
    Edge* edge;
};


int main(){


    return 0;
}

void addVertexToGraph(char data ){

}

void addToLinkedList()