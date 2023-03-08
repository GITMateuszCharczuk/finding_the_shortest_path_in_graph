#ifndef _DIJ_H_
#define _DIJ_H_

#include "grap.h"
#include "que.h"

int *dijstra(graph *g, int start, int stop, int* result);
void dijstra_to_stdout(int *path, int result, int size );

#endif