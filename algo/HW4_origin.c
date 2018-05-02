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

	adj = (int**) malloc ( sizeof(int*) * num );

	for(int i=0; i<num; i++){
		adj[i] = (int*) malloc ( sizeof(int) * num );
	}

	for(int i = 0; i<num; i++)
		for(int j =0; j < num; j++)
			adj[i][j] = data[iter++];

	for(int i = 0; i<num; i++){
		for(int j = 0; j<num; j++)
			printf("%d", adj[i][j]);
		printf("\n");
	}
}

