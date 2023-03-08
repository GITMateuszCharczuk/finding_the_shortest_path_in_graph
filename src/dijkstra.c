#include "dijkstra.h"
#include "graphgen.h"
#include <stdio.h>
#include <stdlib.h>
#define INF 100000.0

void dijstra_to_stdout(int *path, double result)
{
    int i;
    printf("Wartość najkrótszej drogi w grafie: %lf\n",result);
    printf("Kolejne wierzchoki wchodzące w skład najkrótszej drogi:\n");
    for(i = 0; path[i] != -1 ; i++)
    {
        printf("%d ",path[i]);
        if(path[i+1] != -1)
            printf("-> ");
    }

}

int *dijstra(graph *g, int start, int stop, double* result, int w, int l)
{
	int counter = 0;
	int pom;
	int iter = 0;
	int next;
	int n = w * l;
	double distance_min = INF;
	//pque *q = create_pque(1000);
	int* answ = malloc(sizeof(int) * n);
	int* visits = malloc(sizeof(int)  * n);
	int* bef = malloc(sizeof(int)  * n);
	double* distances = malloc(sizeof(double)  * n);
	double** costs = malloc(sizeof(double*) * n);
	for(int i = 0; i < n ; i++){
		costs[i] = malloc(sizeof(double) * n);
	}
	for( int m = 0; m < n ; m++){
		for(int o = 0; o < n; o++){
			costs[m][o] = INF;
		}
		for(int k = 0; k < 4; k++){
			if(g[m].n[k] != -1)
				costs[m][g[m].n[k]] = g[m].w[k];
		}
	}
	for( int k = 0; k < n; k++){
		visits[k] = 0;
		distances[k] = costs[start][k];
		bef[k] = start;
	}
	distances[start] = 0;
	visits[start] = 0;
	iter = 1;
	while(iter < n - 1){
		distance_min = INF;
		for( int i = 0; i < n; i++)
			if(distances[i] < distance_min && !visits[i]){
				distance_min = distances[i];
				next = i;
			}
		visits[next] = 1;
		for(int i = 0; i < n; i++)
			if(!visits[i])
				if(distance_min + costs[next][i] < distances[i]){
					distances[i] = distance_min + costs[next][i];
					bef[i] = next;
				}
		iter++;
	}
	*result = distances[stop]; 
	pom = stop;
	do {
		pom = bef[pom];
		answ[counter] = pom;
		counter++;
	} while(pom != start);
	answ[counter] = -1;
    int *ret = tab_invert(answ,stop);
    return ret;
}

int is_all_used(int *A, int n){
	for(int i = 0; i < n; i++){
		printf("%d -> B[i]", A[i]);
		if(A[i] == 1)
			return 1;
	}
	return 0;
}

int* tab_invert(int *temp, int stop){ // funkcja odwracająca tablicę
    int j=0, siz=0;
    while(temp[siz] != -1){
        siz++;
    }
    int* final = malloc(sizeof(int) * (siz+2));
    siz--;
    for( j = 0; j < siz+1; j++){
        final[j] = temp[siz-j];
    }
    final[siz+1] = stop;
    final[siz+2] = -1;
    return final;
}


