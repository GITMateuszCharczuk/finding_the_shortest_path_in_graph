#ifndef _GR_H_
#define _GR_H_

#include "grap.h"

graph* graph_from_file(char *, int *, int *, int *);
void buff_cleaner(char *, int);
void graph_free(graph*, int);
void graph_filler(graph *, int , int );
#endif
