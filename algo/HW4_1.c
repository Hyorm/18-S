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

	//TODO: read input file and construct Adj array and adjacency list in alphabetical order.
	FILE* fp = fopen("hw4.data", "r") ;
	char buf[10] ;
	int num = 1, iter = 0;
	char* data[100] ;
	char*** adj;
	while(fscanf(fp, "%s", buf)!=EOF)
		data[num++] = buf;

	fclose(fp);
	printf(">%d\n", num);
	num = sqrt(num);

	//construct Adj array

	adj = (char***) malloc ( sizeof(char**) * num );

	for(int i=0; i<num; i++){
		adj[i] = (char**) malloc ( sizeof(char*) * num );
	}
	
	adj[0][0] = "0";

	for(int i = 0; i<num; i++)
		for(int j =0; j < num; j++)
			adj[i][j] = data[iter++];

	for(int i = 0; i<num; i++){
		for(int j = 0; j<num; j++)
			printf("%s", adj[i][j]);
		printf("\n");
	}
}

