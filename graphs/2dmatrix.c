#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex Vertex;

struct Vertex{
    char data;
    int visited;
    int index;
};

// typedef struct Edge Edge;

// struct Edge {
//     Vertex* connectedTo;
//     int weight;
// };

typedef struct LLNode LLNode;

struct LLNode {
    LLNode* next;
    Vertex* vertex;
};

#define NUM_VERTICES 12



Vertex* DFS(Vertex* start,char search, int* cumulativePath);

Vertex* BFS(Vertex* start,char search);

void addNode(Vertex* vertex, LLNode* head){
    LLNode* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));  
    newNode->next = NULL;
    newNode->vertex = vertex;
    temp->next = newNode;
}

LLNode* deleteHead(LLNode* head){
    LLNode* newHead = head->next;
    free(head);
    return newHead;
}




// Array of pointers to vertices
Vertex* graph[NUM_VERTICES];

// Create 2D Matrix of Edge weights (Represent no connection)
// int edges[NUM_VERTICES][NUM_VERTICES]  = {
//     {-1, 1, -1, -1, -1},
//     { 1,-1,  2,  2, -1},
//     {-1, 2, -1, -1,  3},
//     {-1, 2, -1, -1, -1},
//     {-1,-1,  3, -1, -1}
// };


int edges[NUM_VERTICES][NUM_VERTICES] = {
    {-1,1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {1,-1,2,2,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,2,-1,-1,3,2,-1,-1,-1,-1,-1,-1},
    {-1,2,-1,-1,-1,-1,2,-1,-1,-1,-1,-1},
    {-1,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,2,-1,-1,-1,-1,1,2,4,-1,-1},
    {-1,-1,-1,2,-1,-1,-1,-1,-1,1,2,3},
    {-1,-1,-1,-1,-1,1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,2,-1,-1,-1,-1,11,-1},
    {-1,-1,-1,-1,-1,4,1,-1,-1,-1,-1,5},
    {-1,-1,-1,-1,-1,-1,2,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,3,-1,-1,5,-1,-1}
};

int main(){

    // Malloc space and create the vertices    
    for(int i=0;i<NUM_VERTICES;i++){
        graph[i] = (Vertex*)malloc(sizeof(Vertex));
        graph[i]->data = (char)(65+i);
        graph[i]->visited = 0;
        graph[i]->index = i;
    }


    // Debug
    // for(int i=0;i<NUM_VERTICES;i++){
    //     printf("Edge %c connects to: ",graph[i]->data);
    //     for(int j=0;j<NUM_VERTICES;j++){
    //         if(edges[i][j] != -1){
    //             printf("(%c,%i), ",graph[j]->data,edges[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }


    int cumulativePath = 0;
    printf("Depth First Search \n");
    DFS(graph[0],'X',&cumulativePath);
    printf("\nValue of cumulative Path = %i\n",cumulativePath);
    printf("\n");
    for(int i=0;i<NUM_VERTICES;i++){
        graph[i]->visited = 0;
    }


    printf("Breadth First Search \n");
    BFS(graph[0],'X');

    return 0;
}

Vertex* BFS(Vertex* start, char search){
    // Create a queue and add starting node 
    LLNode* head = (LLNode*)malloc(sizeof(LLNode));
    head->vertex = start;
    head->next = NULL;
    //mark it as visited
    head->vertex->visited = 1;

    while(head != NULL){

        printf("%c ",head->vertex->data);
        if(head->vertex->data == search){
            printf("Found %c\n",search);
            return head->vertex;
        }

        // add its connections to list
        for(int j=0;j<NUM_VERTICES;j++){
            if(graph[j]->visited ==0 && edges[head->vertex->index][j] > 0){
               // printf("Adding %C to list\n",graph[j]->data);
                addNode(graph[j],head);
                graph[j]->visited = 1;
            }
        }
       // printf("removnig %c form list\n",head->vertex->data);
        head = deleteHead(head);
    }
    printf("\n%c not contained in the list\n",search);
    return NULL;
}


Vertex* DFS(Vertex* start, char search, int* cumulativePath){
    int cumulativePathCopy = *(cumulativePath);
    start->visited = 1;
    printf("%c ",start->data);
    if(start->data == search){
        printf("\nFound %c at vertex %i\n\n",search,start->index);
        return start;
    }

    for(int j=0;j<NUM_VERTICES;j++){
        // Iterate over its edges
        
        if((edges[start->index][j] != -1) && (graph[j]->visited != 1)){
            cumulativePathCopy += edges[start->index][j];
            //printf("link [%c -> %c] of weight %i found\n",start->data,graph[j]->data, edges[start->index][j]);
            Vertex* result = DFS(graph[j], search, &cumulativePathCopy);

            // Data was found on the lower DFS
            if(result != NULL){
                // Update our real cumulativePath with the value of our local one
                *cumulativePath = cumulativePathCopy;
              
                return result;
            } else {
                // Reset our local one to the real value as data wasn't in lower DFS
                cumulativePathCopy = *cumulativePath;
            }
        }
    }
    return NULL;
}

