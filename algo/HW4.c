#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct _vertex {
        int value ;
        int finishTime ;
	int discoveryTime ;
        struct _vertex * next ;
} vertex ;

vertex* createV(int value);
vertex* makeEdge(vertex* src, int num);
void printVertexs(vertex* src);

static vertex** adjList = 0x0;

int main(){

	char alpha[26] ={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

	FILE* fp = fopen("hw4.data", "r") ;
	char buf[2048] ;
	int num, iter = 0;
	int data[100] ;
	int** adj;

	while(fscanf(fp, "%s", buf)!=EOF){
		if(!isalpha(buf[0]))
			data[num++] = atoi(buf);
	}
	fclose(fp);

	num = sqrt(num);

	//TODO: Construct Adj Array and adjacency list in alphabetical order
	adj = (int**) malloc ( sizeof(int*) * num );

	for(int i=0; i<num; i++){
		adj[i] = (int*) malloc ( sizeof(int) * num );
	}

	for(int i = 0; i<num; i++)
		for(int j =0; j < num; j++)
			adj[i][j] = data[iter++];

	adjList = (vertex**) malloc ( sizeof(vertex*) * num );

	for(int i = 0; i< num; i++){
		adjList[i] = (vertex*)malloc(sizeof(vertex));
		int first = 0;
		for(int j = num; j>=0; j--){
			if(adj[i][j]==1){
				if(first == 0){
					adjList[i] = createV(j);
					first++;
				}
				else{
					adjList[i] = makeEdge(adjList[i], j);
				}	
			}
		}
		if(adjList[i]->next != NULL)adjList[i] = makeEdge(adjList[i], i);
		else adjList[i] = createV(i);
	}

	//TODO: 1) Array of adjacency list of above graph
	printf("1) Array of adjacency list of above graph\n");
	for(int i = 0; i< num; i++)
		printVertexs(adjList[i]);
	
	//TODO: 2) Discovery time and finish time of each vertex after step1 
	printf("2) Discovery time and finish time of each vertex after step1\n");

	//TODO: 3) Array of adjacency list of transpose graph after step2
	printf("3) Array of adjacency list of transpose graph after step2\n");

	//TODO: 4) Discovery time and finish time of each vertex after step3 
	printf("4) Discovery time and finish time of each vertex after step3\n");

	//TODO: 5) SCC result
	printf("5) SCC result\n");
	
	
}

vertex* createV(int value){

	vertex* newVertex = (vertex*)malloc(sizeof(vertex));

        newVertex->value = value;
	int finishTime = 0 ;
	int discoveryTime = 0 ;
        newVertex->next = NULL;
	return newVertex;

}
vertex* makeEdge(vertex* des, int value){

	vertex* newvertex = (vertex*)malloc(sizeof(vertex));
	newvertex->value = value;
	int finishTime = 0 ;
	int discoveryTime = 0 ;
	newvertex->next = des;
	return newvertex;
}
void printVertexs(vertex* src){
	char alpha[26] ={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	vertex * i;

	for (i = src ; i != NULL ; i = i->next)
		printf("%c -> ", alpha[i->value]) ;
	printf("nil\n");

}
