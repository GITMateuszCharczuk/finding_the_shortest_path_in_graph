#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graphgen.h"
#include "graph.h"
#include "dijkstra.h"

//alokuje pamięć na graf
graph* graph_memory_allocator(int rc){
    int i;
    graph* g = (graph*) malloc(rc * sizeof(graph));
    for( i=0 ; i< rc; i++){
        g[i].n = (int*) malloc(sizeof(int) * 4);
        g[i].w = (double*) malloc(sizeof(double) * 4);
    }
    return &(g[0]);
}
//czyści tablicę searched
void searched_cleaner(int *buff){
    int i = 4;
    while(i--)
        buff[i] = 0;
}
//grneruje tablicę potrzebbną do obsługi innych funkcji w obrębie pliku
int** search_graph_gen(int r, int c)
{
    int **buff = (int**) malloc(r * sizeof(int*));
    int i;
    int k;
    int j;
    int  l = 0;
    for(i = 0; i < r; i++)
        buff[i] = (int*) malloc(c * sizeof(int));
    for(k = 0; k < r; k++)
    {
        for(j = 0; j < c; j++)
        {
            buff[k][j] = l;
            l++;
        }
    }
    return buff;
}
//generuje double od s do e
double random_double(double s, double e)
{
    s = s == 0 ? 0.0001 : 0; // warunek nie pozwalający by waga była równa 0
    return s + (e - s) * ((double)rand()/ RAND_MAX);
}
//sprawdza jakie wierzchołki są sąsiadami
int neighbors_gen(int** b, int* s, int x, int y, int c, int r)
{
    
        if(((x+1) >= 0) && (y >= 0) && ((x+1) < r) && (y < c) && (s[0] != 1))
        {
            s[0] = 1;
            return b[x+1][y];
        }
        else
            s[0] = 1;
        if((x-1) >= 0 && y >= 0 && (x-1) < r && y < c && s[1] != 1)
        {
	    s[1] = 1;	
            return b[x-1][y];
        }
        else
            s[1] = 1;
        if(x >= 0 && (y+1) >= 0 && x < r && (y+1) < c && s[2] != 1)
        {
            s[2] = 1;
            return b[x][y+1];
        }
        else
            s[2] = 1;
        if(x >= 0 && (y-1) >= 0 && x < r && (y-1) < c && s[3] != 1)
        {
            s[3] = 1;
            return b[x][y-1];
        }
        else
            s[3] = 1;
        return -1;
    

}
//zwalnia pamięć tablic searched oraz search_graf
void free_graphgen(int **search_graf, int *searched, int r)
{
    int i;
    for(i = 0; i < r; i++)
        free(search_graf[i]);
    free(search_graf);
}
//tworzy graf o podanych wymiarach, generuje wartosci krawedzi i wag
graph* graph_gen(int c, int r, double s, double e){
    srand(time(NULL));
    int i, k, j, l = 0;
    int rc = r * c;
    int searched[4];
    searched_cleaner(&(searched[0]));
    int **search_graf = search_graph_gen(r, c);
    graph* g = graph_memory_allocator(rc);
        for (i = 0; i < r; i++)
        {
            for(j = 0; j < c; j++)
            {
                for (k = 0; k < 4; k++)
                {
                    g[l].n[k] = neighbors_gen(search_graf, searched, i, j, c, r);
                    g[l].w[k] = g[l].n[k] != -1 ? random_double(s,e) : -1;
                }
                searched_cleaner(&(searched[0]));
                l++;
            }
        }
        free_graphgen(search_graf, searched, r);
        return &(g[0]);
}

int graph_slice(graph *g, int n, int r, int c)
{
    int* path;
    int  i,j,k, start;
    double result;
    int stop = (r * c) - 1;
    if(n == 0){
        graph_free(g, r * c);
        exit (EXIT_FAILURE);
    }
    for(k = 0; k < n-1; k++)
    {
        if((2 * (k+1)) < c){
            start = (k * 2);
        }
        else{
            return 1;
        } 
        path = dijstra(g, start, stop, &(result), r, c);
        for(i = 0; path[i] != -1 ; i++)
        {
            for(j = 0; (j < 4) && (g[path[i]].n[j] != -1) ; j++)
            {
                if((path[i]-1) == g[path[i]].n[j])
                {
                    g[path[i]].n[j] = -1;
                    g[path[i]].w[j] = -1;
                }
                if((path[i]+c) == g[path[i]].n[j])
                {
                    g[path[i]].n[j] = -1;
                    g[path[i]].w[j] = -1;
                }
            }
        }
        srt(g, r * c);
    }
    return 0;
}

void srt(graph *g, int rc)
{
    int i,j,k,z;
    int temp[4];
    double temp2[4];
    for(i = 0; i < rc ; i++)
    {
        k=0;
        for(z = 0; z < 4 ; z++)
        {
            temp[k] = -1;
            temp2[k] = -1;
        }
        for(j = 0; (j < 4) ; j++)
        {
            if(g[i].n[j] != -1)
            {
                temp[k] = g[i].n[j];
                temp2[k] = g[i].w[j];
                k++;
            }
        }
        for(j = 0; j < 4; j++)
        {
            if(j < k){
                g[i].n[j] = temp[j];
                g[i].w[j] = temp2[j];
            }else{
                g[i].n[j] = -1;
                g[i].w[j] = -1;
            }
        }
    }
}

void graph_to_file(char* filename, graph *g, int rc, int r, int c)
{
    FILE *out = fopen(filename,"w");
    int i, j = 0;
    fprintf(out,"%d %d\n", r, c);
    for( i = 0; i < rc; i++ ){
        while((g[i].n[j] != -1) && (g[i].w[j] != -1)&&(j < 4))
        {
            fprintf(out,"%d :%lf ",g[i].n[j], g[i].w[j]);
            j++;
        }
        j = 0;
        fprintf(out,"\n");
    }
    graph_free(g, rc);
    fclose(out); 
}