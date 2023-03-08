#include "graphgen.h"
#include "graph.h"
#include "queue.h"
#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>


int bfs(graph* g, int rc,int r,int c){
    que* que; 
    int* visited; 
    int i, item, iserr, size;

    if(c >= r){
        size = r*2 + 1;
    }
    else{
        size = c*2 + 1;
    }

    que = create_que(size); 
    visited = (int*) malloc(sizeof(int) * rc);

    for (i = 0; i < rc; i++){
        visited[i] = 0;
    }

    visited[0] = 1;
    for (i = 0; i < 4; i++){ 
        if (g[0].n[i] != -1){
            iserr = add_que(que, g[0].n[i]);
        }
    }

    while (!is_empty(que)){
        iserr = pop_que(que, &item); 
        if (visited[item] != 1){ 
            visited[item] = 1;

            for (i = 0; i < 4; i++){ 
                if (g[item].n[i] != -1 && visited[g[item].n[i]] == 0){
                    iserr = add_que(que, g[item].n[i]);
                    if (iserr == -1){
                        printf("enqueue failed \n");
                    }
                }
            }
        }
    }

    for (i = 0; i < rc; i++){
        if (visited[i] == 0){
            free(visited);
            free(que);
            return 0;
        }
    }
    free(visited);
    free_que(que);
    return 1;
}





 
