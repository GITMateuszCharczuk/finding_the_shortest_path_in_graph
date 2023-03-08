#ifndef _ERRORSHANDLING_H_
#define _ERRORSHANDLING_H_

#include "graphgen.h"

int is_good_i(char *, int *);
double is_good_d(char *, int *);
int is_file_good(char *);
void check_error_file_format(int, int, int, int*);
void EOFfaliture(char, int, graph *, char *, FILE *);
#endif

