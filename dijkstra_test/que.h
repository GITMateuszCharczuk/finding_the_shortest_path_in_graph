#ifndef _QUE_H_
#define _QUE_H_

#include <stdlib.h>

typedef struct q{
    int* storage;
    int add_indx;
    int pop_indx;
    int act_size;
    int max_size;
} que;

que *create_que(int s);
int is_full(que* q);
int is_empty(que* q);
void free_que(que* q);
void add_que(que* q, int );
int pop_que(que* q);
void double_que_size( que* q );

 
#endif


