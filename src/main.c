#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "errorshandling.h"
#include "graphgen.h"
#include "graph.h"
#include "queue.h"
#include "bfs.h"
#include "dijkstra.h"

char *instructions = 
  "-s wartosc odpowiadajaca numerowi wierzchołka grafu z ktorgo zaczynamy droge\n"
  "-p wartosc odpowiadajaca numerowi wierzchołka grafu do ktorego liczymy droge\n"
  "-m minimalna wartosc wagi\n"
  "-v maksymalna wartosc wagi\n"
  "-c liczba kolumn grafu\n"
  "-r liczba wierszy grafu\n"
  "-n ilosc czesci na ktore zostanie podzielony graf\n"
  "-i nazwa pliku wejściowego\n"
  "-o nazwa pliku wyjściowego\n";

#define STARTING_VERTICLE 's'
#define ENDING_VERTICLE 'p'
#define MINIMUM_WAGE 'm'
#define MAXIMUM_WAGE 'v'
#define GRAPH_COLUMNS 'c'
#define GRAPH_ROWS 'r'
#define GRAPH_SLICE 'n'
#define INPUT_FILE_NAME 'i'
#define OUTPUT_FILE_NAME 'o'
#define HELP_MANUAL 'h'

#define NOT_NUMBER_ERR 1
#define NEGATIVE_NUMBER_ERR 2
#define BAD_IN_FILE_ERR 3 
#define TOO_MANY_SLICES 4

int main(int argc, char**argv)
{
    int opt;
    graph* g = NULL;
    char *temp = NULL;
    int *dijstra_output; // tablica do której zapisujemy wierzchołki wchodzące w skład najkrótszej drogi, generowanej przez dijstrę
    char *inpf = NULL; // nazwa pliku wejściowego
    char *outf = NULL; // nazwa pliku wyjściowego
    int start=-2; //wartosc odpowiadajaca numerowi wierzchołka grafu z ktorgo zaczynamy droge 
    int stop=-2; //wartosc odpowiadajaca numerowi wierzchołka grafu do ktorego liczymy droge
    double min=-2; // minimalna wartosc wagi
    double max=-2; // maksymalna wartosc wagi
    int c=-2; //liczba kolumn grafu
    int r=-2; //liczba wierszy grafu
    int rc;
    int bfsisgood = 1; // jeżeli 1 to graf spójny jak 0 to nie spójny
    double dijstraresult; // dijstra modyfikuje tą zmienną poprzez umieszczenie w niej wartości najkrótszej drogi
    int n=-2; //ilosc czesci na ktore zostanie podzielony graf
    int error_flag = -2;
    int error_flag_filei = -2;

    while ((opt = getopt (argc, argv, "s:p:m:v:c:r:n:i:o:h")) != -1)
    {
        switch (opt)
        {
        case STARTING_VERTICLE:
            temp = optarg;
            start = is_good_i(temp, &(error_flag));
            break;
        case ENDING_VERTICLE:
            temp = optarg;
            stop = is_good_i(temp, &(error_flag));
            break;
        case MINIMUM_WAGE:
            temp = optarg;
            min = is_good_d(temp, &(error_flag));
            break;
        case MAXIMUM_WAGE:
            temp = optarg;
            max = is_good_d(temp, &(error_flag));
            break;
        case GRAPH_COLUMNS:
            temp = optarg;
            c = is_good_i(temp, &(error_flag));
            break;
        case GRAPH_ROWS:
            temp = optarg;
            r = is_good_i(temp, &(error_flag));        
            break;
        case GRAPH_SLICE:
            temp = optarg;
            n = is_good_i(temp, &(error_flag));        
            break;
        case INPUT_FILE_NAME:
            inpf =  optarg;
            error_flag_filei = is_file_good(inpf);
            break;
        case OUTPUT_FILE_NAME:
            outf = optarg;
            break;
        case HELP_MANUAL:
            printf("%s",instructions);
            exit (EXIT_FAILURE);
            break;
        default:                   
        printf ("Podano złą komendę.\n");
        exit (EXIT_FAILURE);
        }
    }
    if(argc == 1)
    {
        fprintf(stderr,"Użytkownik nie podał żadnych argumentów.");
        exit (EXIT_FAILURE);
    }
    if(error_flag_filei == BAD_IN_FILE_ERR)
    {
        fprintf(stderr,"KRYTYCZNY BŁĄD: Podany plik wejściowy nie istnieje\n");
        return BAD_IN_FILE_ERR;
    }else if(inpf != NULL)
    {
        g =  graph_from_file(inpf, &rc, &r, &c);
        if(n != -2){
            if(graph_slice(g, n, r, c) == 1)
            {
                fprintf(stderr,"Nie można podzielić grafu na aż tyle części");
                return TOO_MANY_SLICES;
            }
        }
        bfsisgood = bfs(g, rc, r, c);
        if(bfsisgood == 1){
            printf("Graf jest spójny\n");
            if(start != -2 && stop != -2 && stop < r * c && start < r * c){
                dijstra_output = dijstra(g,start,stop,&(dijstraresult), r, c);
                dijstra_to_stdout(dijstra_output, dijstraresult);
            }else{
                fprintf(stderr,"Podano za mało argumentów by algorytm dijstry mógł znaleść najkrótszą drogę lub wartość końcowa jest za duża lub wartość początkowa jest za duża\n");
            }
        }else
            printf("Graf jest nie spójny\n");
        graph_free(g, rc);
    }
    else if(error_flag == NOT_NUMBER_ERR)
    {
        fprintf(stderr,"KRYTYCZNY BŁĄD: Wartość podana przez użytkownika nie jest liczbą\n");
        return NOT_NUMBER_ERR;
    }else if (error_flag == NEGATIVE_NUMBER_ERR)
    {
        fprintf(stderr,"KRYTYCZNY BŁĄD: Wartość podana przez użytkownika jest ujemna\n");
        return NEGATIVE_NUMBER_ERR;
    }
    else{
        if(c != -2 && r != -2 && min != -2 && max != -2)
        {
            g = graph_gen(c, r, min, max);
            rc = r * c;
            if(n != -2){
                if(graph_slice(g, n, r, c) == 1)
                {
                    fprintf(stderr,"Nie można podzielić grafu na aż tyle części");
                    return TOO_MANY_SLICES;
                }
            }
            bfsisgood = bfs(g, rc, r, c);
            if(bfsisgood == 1){
                printf("Graf jest spójny\n");
                if(start != -2 && stop != -2 && stop < r * c && start < r * c){
                   dijstra_output = dijstra(g,start,stop,&(dijstraresult) , r, c);
                   dijstra_to_stdout(dijstra_output, dijstraresult);
                }else{
                    fprintf(stderr,"Podano za mało argumentów by algorytm dijstry mógł znaleść najkrótszą drogę lub wartość końcowa jest za duża lub wartość początkowa jest za duża\n");
                }
            }else{
                printf("Graf jest nie spójny\n");
            }
            if(outf != NULL)
                graph_to_file(outf, g, r*c, r, c);
            else
                graph_free(g, r * c);
        }else{
            fprintf(stderr,"Nie podano wystarczającej ilości argumentów aby wygenerować graf\n");
        }
    }
    return 0;
}
