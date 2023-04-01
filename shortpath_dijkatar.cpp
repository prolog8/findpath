#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

#define MAX 20

int V;	// Total number of nodes

int minDistance(int dist[], bool sptSet[]) 
{ 
	// Initialize min value 
    int min = 999, min_index=0; 
  
    for (int v = 0; v < V; v++){
        if (sptSet[v] == false){
			if (dist[v] < min){
				min = dist[v]; min_index = v;
            } 
		}
    }
                    
	return min_index; 
}
        
void dijkstra(int8_t graph[MAX][MAX], int src, int dist[], int parent[])
{
    bool sptSet[V];

    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        dist[i] = 999;
		sptSet[i] = false;
	}

    dist[src] = 0;

    for (int count = 0; count < V; count++)
    {
		int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
        {
			if (!sptSet[v] && graph[u][v]!=0 && dist[u] + graph[u][v] < dist[v])
            {
				parent[v] = u;
                dist[v] = dist[u] + graph[u][v]; 
            }
        }

    }

}        

void AssignArray(int a[], int8_t graph[MAX][MAX]){
	for(int i=0; a[i] != -99; ){
		int s=a[i];
		//printf("%d: ", s);
		for(int k=i+1;;){
			graph[s][a[k]]=1;
			//printf("%d ", a[k]);
			k++;
			if(a[k]==-1){i=k+1;break;}
			if(a[k]==-99){i=k;break;}
		}
		//printf("\n");
	}
}

void copyParent(int src, int V, int parent[], int8_t Parents[MAX][MAX]){
	for (int i = 0; i < V; i++) {
		Parents[src][i] = parent[i];
    }
}

void generateParent(int8_t graph[MAX][MAX], int8_t Parents[MAX][MAX]){
	int parent[V];
    int dist[V];
	
	for(int i=0; i<V; i++){
		dijkstra(graph, i, dist, parent);
		copyParent(i, V, parent, Parents);
	}
}

void getPath(int src, int des, int Res[], int8_t parents[MAX][MAX]) 
{ 
	int c=0, L[MAX];
	for(;des>=0;){ L[c++]=des; des=parents[src][des]; }
	for(int i=0; i<c; i++)Res[i]=L[c-i-1];
	Res[c]=-1;
}  

void defineEdges(int8_t graph[MAX][MAX]) {
  V = 17;

  // Clear
  for (int i = 0; i < MAX; i++)for (int k = 0; k < MAX; k++)graph[i][k]=0;
  
  int a[] = {
	  0, 1, 2, 3, -1,
	  1, 0, 5, 6, -1,
	  2, 3, -1,
	  3, 0, 2, 4, -1,
	  4, 3, 5, 8, 9, -1,
	  5, 1, 4, 6, -1,
	  6, 1, 5, -1,
	  7, 8, 11, 12, -1,
	  8, 4, 7, 9, -1, 
	  9, 4, 8, 10, -1,
	  10, 9, 15, 16, -1,
	  11, 7, 12, -1,
	  12, 7, 11, 13, -1,
	  13, 12, 14, -1,
	  14, 13, 15, -1,
	  15, 10, 14, 16, -1,
	  16, 10, 15, -99
	};
	
	AssignArray(a, graph);
}


void printPath(int path[]){
	for(int i=0; path[i]>=0; i++)printf("%d ", path[i]);		
}



void printParent(int8_t Ps[MAX][MAX]){
	for(int i=0; i<V; i++){
		printf("%d:", i);
		for(int k=0; k<V; k++){
			printf("%d ", Ps[i][k]);
		}
		printf("\n");
	}
}

int main() {

    int8_t graph[MAX][MAX];
	int8_t Parents[MAX][MAX];
	int Path[MAX];
	
    defineEdges(graph);
	
	generateParent(graph, Parents);
	
	printParent(Parents);
	
	
	getPath(0, 16, Path, Parents);
	printPath(Path);
	
	printf("\n");
	
	getPath(3, 12, Path, Parents);
	printPath(Path);

	printf("\n");
	
	getPath(1, 16, Path, Parents);
	printPath(Path);
	

}
