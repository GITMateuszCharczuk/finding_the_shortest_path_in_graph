#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "err.h"

#include "grap.h"
#include "gr.h"

#define HYPHEN 45
#define SLASH 47
#define COLON 58
#define COMMA 44
#define DOTT 46

int is_good_i(char *buf, int *err)
    {
        int j = strlen(buf);
        int return_value;

        while(j--)
        {
            if((buf[j] == HYPHEN)&&(j == 0)) //wyeliminowanie sytuacji rozpoznawania liczby ujemnej jako nie liczbę przez pentlę
                break;
            if((buf[j] > SLASH && buf[j] < COLON))
                continue;

            *err = 1;
            break;
        }
        if(((*err) != 1) && ((*err) != 2)){
            *err = atoi(buf) >= 0 ? *err : 2;
            return_value = *err != 2 ? atoi(buf) : -1;
            return return_value;
        }else{
            return -1;
        }
    }

double is_good_d(char *buf, int *err)
    {
        int j = strlen(buf);
        double return_value;
        while(j--)
        {
            if(buf[j] == COMMA) /// warunek dzięki któremu liczbą rozdzielona '.' zostanie rozpoznana jako liczba
                buf[j] = '.';
            if(buf[j] == DOTT) // warunek dzięki któremu liczbą rozdzielona '.' zostanie rozpoznana jako liczba
                continue;
            if((buf[j] == HYPHEN)&&(j == 0)) //wyeliminowanie sytuacji rozpoznawania liczby ujemnej jako nie liczbę przez pentlę
                break;
            if(buf[j] > SLASH && buf[j] < COLON)
                continue;

            *err = 1;
            break;
        }
        if(((*err) != 1) && ((*err) != 2)){
            *err = atof(buf) >= 0.0 ? *err : 2;
            return_value = *err != 2 ? atof(buf) : -1;
            return return_value;
        }else{
            return -1;
        }
    }
int is_file_good(char *f_name)
    {
        FILE *check = fopen(f_name,"r");
        if(check == NULL){
            return 3;
        }else{
            fclose(check);
            return 0;
        }
    }

void check_error_file_format(int error_flag_3, int error_flag_1,int error_flag_2, int* error_flag_4)
    {
            if(error_flag_3 == 1)
            {
                fprintf(stderr,"Format pliku jest niepoprawny(entery)\n");
                *error_flag_4 = 1;
            }
            if(error_flag_2 == 1)
            {
                fprintf(stderr,"Format pliku jest niepoprawny(brakuje : przed wagą)");
                *error_flag_4 = 1;
            }
            if(error_flag_1 == 1)
            {
                fprintf(stderr,"Format pliku jest niepoprawny: wartości podane przez użytkownika nie są liczbami\n");
                *error_flag_4 = 1;
            }else if(error_flag_1 == 1)
            {
                fprintf(stderr,"Format pliku jest niepoprawny: liczby podane przez użytkownika są ujemne\n");
                *error_flag_4 = 1;
            }
    }

void EOFfaliture(char isEOF, int rc, graph *g, char *tmp, FILE *in)
    {
        if(isEOF == EOF)
        {
            fprintf(stderr,"Format pliku jest niepoprawny(EOF)\n");
            free(tmp);
            fclose(in);
            graph_free(g, rc);
            exit(2);
        }
    }