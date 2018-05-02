#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct _vertex {
        char * value ;
        int finishTime ;
	int discoveryTime ;
        struct _vertex * next ;
} vertex ;

vertex * vertex_list = 0x0 ;
int main(){

	char alpha[26] ={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

	//DONE: Read Input File
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

	//TODO: 1) Array of adjacency list of above graph
	printf("1) Array of adjacency list of above graph\n");
	
	
}

