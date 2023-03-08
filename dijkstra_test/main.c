#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dij.h"
#include "err.h"
#include "gr.h"
#include "grap.h"
#include "que.h"

int main(){
    int result;// tu się wynik zapisze
    int *path;//tu się ścierzka wierzchołków najkrótszej drogi zapisze
    int start = 0;//numer 1 wierzchołka
    int stop = 10;//numer ostatniego wierzchołka
    graph *g = graph_gen(4, 4, 0, 2);//tu sobie możesz pozamieniać jak chcesz
    graph_to_file("chuj.txt" , g, 16, 4, 4);
    // path = dijstra(g, start, stop, &result);
    // dijstra_to_stdout(path, result, sizeof(path) );// to nie testowałem czy działa ale powino chyba
    return 0;
}