#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

que *create_que(int s){
    que* q = (que*) malloc(sizeof(que));
    q->front = -1;
    q->back = -1;
    q->size  = s;
    q->items = (int*) malloc(sizeof(int) * s);
    return q;
}

void free_que(que* q){
    free(q->items);
    free(q);
}

int is_empty(que* q){
     if(q->front == -1){
        return 1;
    }
    return 0;
}

int is_full(que* q){
     if((q->front == q->back + 1) || (q->front == 0 && q->back == q->size -1)){
        return 1;
    }
    return 0;
}

int add_que(que* q, int item){
    if(is_full(q)){
        return -1;
    }
    if(q->front == -1){
        q->front = 0;
    }
    q->back = (q->back + 1) % q->size;
    q->items[q->back] = item;
    return 0;
}

int pop_que(que* q, int* item){
    if(is_empty(q)){
        return -1;
    }
    (*item) = q->items[q->front];
    if(q->front == q->back){
        q->front = -1;
        q->back = -1;
    }
    else{
        q->front = (q->front + 1) % q->size;
    }
    return 0;
}

