#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "graph.h"
#include "graphgen.h"
#include "errorshandling.h"

#define SIZE 50
#define NEW_LINE 10
#define CARRIAGE 13
#define COLON 58

void buff_cleaner(char *buff, int i)
{
    int x = i;
    while(x--)
        buff[x] = '\0';
}
void graph_filler(graph *g, int j, int k)
{
    int i;
    for(i = k + 1; i < 4; i++)
    {
        g[j].n[i] = -1;
        g[j].w[i] = -1;
    }
}

graph* graph_from_file(char *fname, int *rowcol, int *row, int *col)
{
    char tmp;

    graph* g= NULL;
    int r, c, i, j, k = 0;
    int error_flag_1 = 0;
    int error_flag_2 = 0;
    int error_flag_3 = 0;
    int error_flag_4 = 0;
    FILE *in = fopen(fname,"r");
    char *buff = malloc(SIZE * sizeof(int));
    if(fgets( buff, SIZE, in ) != NULL)
    {
        if( sscanf( buff, "%d  %d", &r, &c) == 2 )
            {
                *row = r;
                *col = c;
            }
        else{
            fprintf(stderr,"Format pliku jest niepoprawny( 1 linijka )");
            free(buff);
            fclose(in);
            exit(4);
            }
    }
    int rc = r * c;
    *rowcol = rc;
    g = graph_memory_allocator(rc);
    for( j = 0; j < rc; j++)
    {   
        for( k = 0; k < 4; k++)
        {
            do{
                tmp = fgetc(in);
                error_flag_3 = tmp == NEW_LINE ? 1 : error_flag_3;
                EOFfaliture(tmp, rc, g, buff, in);
            }while(isspace(tmp) != 0);
            buff[0] = tmp;
            for(i = 1; isspace(tmp) == 0; i++)
            {
                tmp = fgetc(in);
                buff[i] = tmp;
            }
            error_flag_3 = buff[i-1] == NEW_LINE ? 1 : error_flag_3;
            EOFfaliture(buff[i-1], rc, g, buff, in);
            buff[i-1] = '\0';
            g[j].n[k] = is_good_i(buff, &error_flag_1);
            buff_cleaner(buff,i);
            do{
                tmp = fgetc(in);
                error_flag_3 = tmp == NEW_LINE ? 1 : error_flag_3;
                EOFfaliture(tmp, rc, g, buff, in);
            }while(isspace(tmp) != 0);
            error_flag_2 = tmp != COLON ? 1 : error_flag_2;
            for(i = 0; isspace(tmp) == 0; i++)
            {
                tmp = fgetc(in);
                buff[i] = tmp;
            }
            error_flag_3 = buff[i-1] == NEW_LINE ? 1 : error_flag_3;
            EOFfaliture(buff[i-1], rc, g, buff, in);
            buff[i-1] = '\0';
            g[j].w[k] = is_good_d(buff, &error_flag_1);
            buff_cleaner(buff,i);
            check_error_file_format(error_flag_3, error_flag_1, error_flag_2, &(error_flag_4));
            if(error_flag_4)
            {
                graph_free(g, rc);
                free(buff);
                fclose(in);
                exit(1);
            }
            do{
                tmp = fgetc(in);
                if(tmp == NEW_LINE)
                {
                    graph_filler(g, j, k);
                    k = 4;
                    continue;
                }
                if((tmp == EOF) && (j == rc-1))
                {
                    free(buff);
                    fclose(in);
                    return &(g[0]);
                }
                if((tmp == EOF) && (j < rc-1)){
                    EOFfaliture(EOF, rc, g, buff, in);
                }
            }while(isspace(tmp) != 0);
            ungetc(tmp,in);
        }
    }
    return &(g[0]);
}

void graph_free(graph* g, int rc)
{
    int i;
    if(g != NULL){
        for( i=0 ; i< rc; i++){
            free(g[i].n);
            free(g[i].w);
        }
        free(g);
    }
}
