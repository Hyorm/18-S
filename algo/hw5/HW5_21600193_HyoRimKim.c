#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <queue>
#include <stack>

typedef struct _vertex {
        struct _vertex * parent = 0x0 ;
        char* value ;
        char* distance = "INF" ;
} vertex ;


int main(int argc, char *argv[]){

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
	int num, iter = 0;
	char* data[300];

	char*** adj;
	
	data[0] = "";
	while(fscanf(fp,"%s", buf)!=EOF){
		num++;
		int l = strlen(buf);
		data[num] = (char*)malloc(sizeof(char) * (l + 1));
		strcpy(data[num], buf);
	}
	fclose(fp);

	num = sqrt(num+1);

	//DONE: Create data structure for a given graph
	adj = (char***) malloc ( sizeof(char**) * num );

	for(int i=0; i<num; i++){
		adj[i] = (char**) malloc ( sizeof(char*) * num );
	}
	for(int i = 0; i<num; i++)
		for(int j =0; j < num; j++){
			adj[i][j] = data[iter++];
		}

	/*//print point 1
	for(int i = 0; i< num; i++){
		for(int j =0; j < num; j++){
			printf("%10s", adj[i][j]);
		}
		printf("\n");
	}
	*/

	//TODO:1) Apply Dijkstra's algorithm for |V| times and print result

	//(1) make priority queue

	//(2) INITIALIZE-SINGLE-SOURCE(G, s)

	//(3) DIJKSTRA(G,w,s)

	

	

	//TODO:2) Apply Bellman-Ford's algorithm for |V| times and print result


	//TODO:3) Run Floyd’s algorithm and print result



	//TODO: Free all allocation memory
	for (int i = 0; i < num; i++){
		free(adj[i]);
	}
	free(adj);
	free(data);
}
