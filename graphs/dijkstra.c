#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex Vertex;

struct Vertex{
    char data;
    int visited;
    int index;

    // Dijkstra
    int runningCost;
    Vertex* parent;
};


#define NUM_VERTICES 12

// Array of pointers to vertices
Vertex* graph[NUM_VERTICES];

// Dijkstra Permanent set will contain all nodes
Vertex* dijkPermSet[NUM_VERTICES];


int dijkstra(Vertex* current, char search);





// 2D matrix representing assignment graph
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

    printf("Dijkstra \n");
    dijkstra(graph[0],'x');

    return 0;
}



int dijkstra(Vertex* current, char search){


    /**
        1: Add current vertex to the permanent set and mark as visited
    */
    for(int i=0;i<NUM_VERTICES;i++){
        if(dijkPermSet[i] == NULL){
            dijkPermSet[i] = current;
            current->visited = 1;
            break;
        }
    }

    // Print visiting
    if(current->parent != NULL){
        printf("Visted %c, length = %i, parent = %c\n",current->data,current->runningCost,current->parent->data);
    } else {
        printf("Visted %c, length = %i\n",current->data,current->runningCost);
    }
    

    // Found data we were looking for
    if(current->data == search){
        printf("%c found, shortest cost = %i \n",current->data,current->runningCost);
        return 1;
    }


    /**
        2:  Look at all vertices in permanent set
                Examine the running costs from each of these to each vertex they are connected to 
                that is not in the permanent set already
            Next Vertex in permanent set is minimum of these.
                ** Chosen AFTER looking at all vertices in permanent set
    */

    Vertex* nextVertex = NULL;
    int currentMin = 9999;

    // Iterate over permanent set until NULL reached
    for(int i=0;i<NUM_VERTICES;i++){

        if(dijkPermSet[i] == NULL){
            // break when we reach end of permanent set
            break;
        }

       // need this nodes row reference to 2d matrix
        int currentVertexIndex = dijkPermSet[i]->index;

        // Iterate over all of its connected edges
        for(int j=0;j<NUM_VERTICES;j++){
            if(graph[j]->visited == 0 && edges[currentVertexIndex][j] != -1){

                // connection to this vertex and it's not in permanent set
                int runningToHere = graph[currentVertexIndex]->runningCost + edges[currentVertexIndex][j];
                if(runningToHere < currentMin){
                    currentMin = runningToHere;
                    nextVertex = graph[j];
                    nextVertex->parent = graph[currentVertexIndex];
                }
            }
        }
    }


    /**
        3: If next vertex was found, set its running cost and recurse using that as current vertex
                Otherwise return as have visited all vertices on the graph
    */
    if(nextVertex != NULL){
        nextVertex->runningCost = currentMin;
        return dijkstra(nextVertex,search);
    } else {
        printf("next vertex null, returning\n");
        return 0;
    }    
}

