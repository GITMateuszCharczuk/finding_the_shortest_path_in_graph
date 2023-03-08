#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>

typedef struct que{
    int* items;
    int front;
    int back;
    int size;
} que;

que *create_que(int);
int is_full(que* q);
int is_empty(que* q);
void free_que(que* q);
int add_que(que* q, int );
int pop_que(que* q, int *);

 
#endif


