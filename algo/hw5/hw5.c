#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define INF 999999999

typedef struct _vertex {
	struct _vertex* parent ;
        char* value ;
        int distance ;
	struct _vertex* next ; 
} vertex ;

typedef struct _edge {
	struct _vertex* source ;
	struct _vertex* dest;
	int distance;
} edge;

vertex** heap;
vertex** shortVertex;
edge** edgeSet;
int edgeNum=0;
int last = 0;
char*** adj;
void relax(vertex* u,vertex* v, int w);
void dijkstra(vertex** bigV, char* s);

void floyd_warshall(char*** reFloyd);

int findMin(int idx);
vertex* extract_min();
void enqueue(vertex* v);
void init_single_source(vertex** bigV, char* s);
int num;
bool bellman_ford(vertex** bigV, char* s);

int main(int argc, char *argv[]){

	double start, finish, duration = 0;

	//DONE: Read input file
	FILE*fp;

	if(argc>1)fp = fopen(argv[1], "r");
	else if(argc==1)fp = fopen("hw5.data", "r") ;
	else {
		printf("file name error --> use default file");
		fp = fopen("hw5.data", "r") ;
	}

	if(fp==NULL){
		printf("file open error\n");
		exit(1);
	}	

	char buf[2048];
	int iter = 0;
	char* data[300];
	num = 0;
	data[0] = "";
	while(fscanf(fp,"%s", buf)!=EOF){
		num++;
		int l = strlen(buf);
		data[num] = (char*)malloc(sizeof(char) * (l + 1));
		strcpy(data[num], buf);
	}
	fclose(fp);

	num = sqrt(num);

	heap = (vertex**) malloc(sizeof(vertex*)*num);
	for(int i=1; i<num+1; i++)
		heap[i] = (vertex*) malloc(sizeof(vertex)*num);

	//DONE: Create data structure for a given graph
	adj = (char***) malloc ( sizeof(char**) * num+1 );

	for(int i=0; i<num+1; i++){
		adj[i] = (char**) malloc ( sizeof(char*) * num+1 );
	}
	for(int i = 0; i<num+1; i++)
		for(int j =0; j < num+1; j++){
			adj[i][j] = data[iter++];
		}	
	printf("0) INPUT\n\n");	
	//print point 1
	for(int i = 0; i< num+1; i++){
		for(int j =0; j < num+1; j++){
			printf("%10s", adj[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");

	//DONE:1) Apply Dijkstra's algorithm for |V| times and print result

	//(1) make priority queue
	vertex** bigV;
        bigV = (vertex**) malloc(sizeof(vertex*)*num);
        for(int i=0; i<num; i++){
                bigV[i] = (vertex*) malloc(sizeof(vertex)*num);
                bigV[i]->value = adj[0][i+1];
        }

	char*** reDijkstra = (char***) malloc ( sizeof(char**) * num+1 );

	for(int i=0; i<num+1; i++){
		reDijkstra[i] = (char**) malloc ( sizeof(char*) * num+1 );
		for(int j=0; j<num+1; j++)
			reDijkstra[i][j] =  adj[i][j];
	}
	start = 0;
        finish = 0;
        duration = 0;

	//(2) DIJKSTRA(G,w,s)
        for(int i=0; i<num; i++){
		start = clock();
                dijkstra(bigV, adj[0][i+1]);
		finish = clock();
		duration += ((double)(finish - start)/CLOCKS_PER_SEC);
		for(int j = 0; j<num; j++){
			for(int k = 0; k<num; k++){
				if(!strcmp(shortVertex[k]->value, adj[j+1][0])){
					char* buffer = (char*) malloc ( sizeof(char) * num);
					sprintf(buffer, "%d",shortVertex[k]->distance);
					reDijkstra[j+1][i+1] = buffer;
				}
			}
		}
		
	}

	printf("a) Apply Dijkstra's algorithm |V| times on each vertex.\n It took %f seconds to compute shortest path between cities with Dijkstra's algorithm as follows.\n\n", duration);

	for(int i=0; i<num+1; i++){
		for(int j = 0; j<num+1; j++)
			printf("%10s", reDijkstra[i][j]);
		printf("\n");
	}
	printf("\n\n");
	
	//TODO:2) Apply Bellman-Ford's algorithm for |V| times and print result

	//make EdgeSet

	edgeSet = (edge**) malloc(sizeof(edge*)*num*num);
        for(int i=0; i<num*num; i++)
                edgeSet[i] = (edge*) malloc(sizeof(edge)*num*num);

	for(int i = 0; i<num+1; i++){
		for(int j = 0; j<num+1; j++){
			if(strcmp(adj[i][j], "INF")){
				if(atoi(adj[i][j])!=0){
					for(int k = 0; k<num; k++)
						if(!strcmp( adj[i][0], bigV[k]->value))
							edgeSet[edgeNum]->source = bigV[k];
					for(int k = 0; k<num; k++)
                	                        if(!strcmp(adj[0][j], bigV[k]->value))
                	                                edgeSet[edgeNum]->dest = bigV[k];
					edgeSet[edgeNum]->distance = atoi(adj[i][j]);
					edgeNum++;
				}	
			}
		}
	}


	char*** reBellman = (char***) malloc ( sizeof(char**) * num+1 );

        for(int i=0; i<num+1; i++){
                reBellman[i] = (char**) malloc ( sizeof(char*) * num+1 );
                for(int j=0; j<num+1; j++)
                        reBellman[i][j] =  adj[i][j];
        }

	bool rebell;
        start = 0;
        finish = 0;
        duration = 0;
        for(int i=0; i<num; i++){
                start = clock();
                rebell = bellman_ford(bigV, adj[0][i+1]);
                finish = clock();
                duration += ((double)(finish - start)/CLOCKS_PER_SEC);
                for(int j = 0; j<num; j++){
                        for(int k = 0; k<num; k++){
                                if(!strcmp(bigV[k]->value, adj[j+1][0])){
                                        char* buffer = (char*) malloc ( sizeof(char) * num);
                                        sprintf(buffer, "%d",bigV[k]->distance);
                                        reBellman[j+1][i+1] = buffer;
                                }
                        }
                }                
	}

	printf("b) Apply Bellman-Ford algorithm |V| times on each vertex.\n It took %f seconds to compute shortest path between cities with Bellman Ford algorithm as follows.\n\n", duration);

	if(!rebell)
		printf(" Negative edge weight cycles detected\n");
	else
		printf(" No Negative edge weight cycles\n");

        for(int i=0; i<num+1; i++){
                for(int j = 0; j<num+1; j++)
                        printf("%10s", reBellman[i][j]);
                printf("\n");
        }
	printf("\n\n");

	//TODO:3) Run Floyd’s algorithm and print result

        char*** reFloyd = (char***) malloc ( sizeof(char**) * num+1 );

        for(int i=0; i<num+1; i++){
                reFloyd[i] = (char**) malloc ( sizeof(char*) * num+1 );
		for(int j = 0; j<num+1; j++)
                       reFloyd[0][j] = adj[0][j];
		reFloyd[i][0] = adj[i][0];
        }
	start = 0;
	finish = 0;
	duration = 0;
	start = clock();
	floyd_warshall(reFloyd);
	finish = clock();
	duration += ((double)(finish - start)/CLOCKS_PER_SEC);
	printf("c) Apply Floyd’s algorithm.\n It took %f seconds to compute shortest path between cities with Floyd algorithm as follows.\n\n", duration);

	for(int i=0; i<num+1; i++){
                for(int j = 0; j<num+1; j++)
                        printf("%10s", reFloyd[i][j]);
                printf("\n");
        }

	printf("\n\n");
	//TODO: Free all allocation memory
	for (int i = 0; i < num+1; i++)
		free(adj[i]);
	free(adj);
	for(int i = 0; i < num; i++)
                free(bigV[i]);
        free(bigV);
/*
	for(int i = 0; i < num; i++)
		free(heap[i]);
	free(heap);
*/
	for(int i = 0; i < num; i++)
		free(edgeSet[i]);
	free(edgeSet);
}
int findMin(int cur){
	int left = 2*cur;
	int right = left + 1;

	if(right > last)
		return left;
	
	if(heap[left]->distance<heap[right]->distance)
		return left;
	else
		return right;

}
vertex* extract_min(){

	vertex* min = (vertex*)malloc(sizeof(vertex));
	if(last<1)
		return min;

	min = heap[1];
	heap[1] = heap[last];
	last--;

	int cur = 1;

	while(1){

		int left = 2*cur;
		int right = left+ 1;

		if(left > last)
			break;
			
		int minIdx = findMin(cur);


		if(heap[cur]->distance<heap[minIdx]->distance)
			break;
		else{
			vertex* temp = (vertex*)malloc(sizeof(vertex));
			temp = heap[minIdx];
			heap[minIdx] = heap[cur] ;
			heap[cur] = temp ;
			cur = minIdx;
		}
	}
	return min;

}
void enqueue(vertex* v){
	last++;
	heap[last] = v;
	int cur = last;
	
	int parentIdx = cur/2;
	
	while(1){

		if(parentIdx < 1)
			return ;
		if(heap[cur]->distance > heap[parentIdx]->distance)
			return;
		vertex* temp = (vertex*)malloc(sizeof(vertex));
		temp = heap[cur];
		heap[cur] = heap[parentIdx];
		heap[parentIdx] = temp;
		cur = parentIdx;
		parentIdx = cur/2;
	}

}
void init_single_source(vertex** bigV, char* s){
	for(int i = 0; i < num; i++){
		bigV[i]->distance = 999999999;
		bigV[i]->parent = NULL;
	}
	for(int i = 0; i < num; i++)
		if(!strcmp(bigV[i]->value, s))
			bigV[i]->distance = 0;
}
void relax(vertex* u,vertex* v, int w){
	if(v->distance > u->distance+w){
		v->distance = u->distance+w;
		v->parent = u;
	}
}
void dijkstra(vertex** bigV, char* s){

	last = 0;	
	//1)INITIALIZE-SINGLE-SOURCE(G, s)
	init_single_source(bigV, s);
	//2)S ← Ø
        shortVertex = (vertex**) malloc(sizeof(vertex*)*num);
	for(int i=0; i<num; i++)
                shortVertex[i] = (vertex*) malloc(sizeof(vertex)*num);

	//3)Q ← V[G]
	for(int i=0; i<num; i++)
                enqueue(bigV[i]);
	//4)while Q ≠ Ø
	while(last>0){
		vertex* u = (vertex*)malloc(sizeof(vertex));
	//5)do u ← EXTRACT-MIN(Q)
		u = extract_min();
	//6)S ← S U {u}

	int exist = 0;

	for(int i = 0; i< num-last-1; i++)
		if(!strcmp(shortVertex[i]->value,u->value))
			exist++;
		
	if(exist==0)
		shortVertex[num-last-1] = u;

	//7)for each vertex v ∈ Adj[u]
		for(int i = 1; i< num+1; i++){
			if(!strcmp(adj[0][i],u->value)){
				for(int j = 1; j<num+1; j++){
					if(strcmp(adj[j][i], "INF")){
						for(int k = 0; k<num;k++)
							if(!strcmp(adj[j][0],bigV[k]->value)){
								//8)do RELAX(u, v, w)
								relax(u, bigV[k], atoi(adj[j][i]));
						}
					}
				}
			}
		}
	}

}
bool bellman_ford(vertex** bigV, char* s){
	
	init_single_source(bigV, s);

	for(int i = 1; i<num; i++)
		for(int j = 0; j<edgeNum; j++)
			for(int k = 0; k<num; k++)
				if(!strcmp(bigV[k]->value, edgeSet[j]->source->value))
					for(int l = 0; l<num; l++)
						if(!strcmp(bigV[l]->value, edgeSet[j]->dest->value)){
							relax(bigV[k], bigV[l], edgeSet[j]->distance);
						}	
	for(int i = 0; i<edgeNum; i++)
		for(int j = 0; j<num; j++)
			if(!strcmp(bigV[j]->value, edgeSet[i]->source->value))
				for(int k = 0; k<num; k++)
					if(!strcmp(bigV[k]->value, edgeSet[i]->dest->value))
						if(bigV[k]->distance > bigV[j]->distance+edgeSet[i]->distance){
							return false;
							}
	return true;
}
void floyd_warshall(char*** reFloyd){
	for(int i = 1; i<num+1; i++)
		for(int j = 1; j<num+1; j++)
			reFloyd[i][j] = adj[i][j];
	
	for(int k = 1; k<num+1; k++)
		for(int i = 1; i<num+1; i++)
			for(int j = 1; j<num+1; j++){
				int ik;
				if(strcmp(reFloyd[i][k],"INF"))
					ik = atoi(reFloyd[i][k]);
				else ik = INF;
				int kj;
				if(strcmp(reFloyd[k][j],"INF"))
                                        kj = atoi(reFloyd[k][j]);
                                else kj = INF;
				int ij;
				if(strcmp(reFloyd[i][j],"INF"))
                                        ij = atoi(reFloyd[i][j]);
                                else ij = INF;
				if (ik+kj < ij) {
                     			char* buffer = (char*) malloc ( sizeof(char) * num);
                                       	sprintf(buffer, "%d",ik+kj);
					reFloyd[i][j] = buffer;

				}

			}
	
}
