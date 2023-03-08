#include <stdio.h>
#include <stdlib.h>

#include "que.h"

que *create_que(int s){
    que* q = (que*) malloc(sizeof(que));
    q->add_indx = 0;
    q->pop_indx = 0;
    q->act_size = 0;
    q->max_size = s;
    q->storage = (int*) malloc(sizeof(int) * s);
    return q;
}

void free_que(que* q){
    free(q->storage);
    free(q);
}

int is_empty(que* q){
    if(q->act_size == 0){
        return 1;
    }
    return 0;
}

int is_full(que* q){
    if(q->act_size == q->max_size){
        return 1;
    }
    return 0;
}

void add_que(que* q, int item){
    if(is_full(q)){
        double_que_size( q );
    }
    q->storage[q->add_indx] = item;
    q->add_indx++;
    q->act_size++;
}

int pop_que(que* q){
    if(is_empty(q)){
        return -1;
    }
    int return_value = q->storage[q->pop_indx];
    q->storage[q->pop_indx] = '\0';
    q->act_size--;
    q->pop_indx++;
    return return_value;
}

void double_que_size( que* q ) {// do puci realloc jest byqqqq
    int j = q->max_size;
	q->storage = realloc( q->storage, 2 * j * sizeof(int) );
	q->max_size = 2 * q->max_size;
}

