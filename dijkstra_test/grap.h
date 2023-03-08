#ifndef _GRAP_H_
#define _GRAP_H_

typedef struct graph{
    int* n; // sąsiedzi
    double* w; // wagi połączeń
} graph;

graph* graph_memory_allocator(int );
int** search_graph_gen(int , int );
void searched_cleaner(int *);
double random_double(double , double );
int neighbors_gen(int** , int* , int , int , int , int );
graph* graph_gen(int , int , double , double );
void graph_to_file(char* , graph *, int, int, int);
void free_graphgen(int **, int *, int);
int graph_slice(graph *, int , int, int);
void srt(graph *,int );
#endif
