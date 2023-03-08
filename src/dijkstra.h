#ifndef _DIJKSTRA_H_
#define _DISJKSTRA_H_

#include "graphgen.h"

int *dijstra(graph *g, int start, int stop, double* result, int w, int l);
void dijstra_to_stdout(int *path, double result);
int is_all_used(int A[], int n);
int* tab_invert(int *temp, int stop);
#endif