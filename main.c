#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "filesystem.h"
#define MAX_SIZE_IN_BUFFER 96
#define EXIT 'exit'

char command;
char command_buffer[MAX_SIZE_IN_BUFFER];
int char_count;
int var = 1;

void cleartoendofline( void )
{
    char command;
    command = getchar();
    while( command != '\n' ){
        command = getchar();
    }
}

void presentation(){
    printf("Enter a line of text (<96 chars)\n");
    while(var == 1){
        command = getchar();
        char_count = 0;
        while( (command != '\n')  &&  (char_count < MAX_SIZE_IN_BUFFER)) {
            command_buffer[char_count++] = command;
            command = getchar();
        }
        if(!strcmp(command_buffer, "exit")){
            var = 0;
        }
    }
}


int main(int argc, char **argv)
{
    //presentation();

    if (argc == 3){
        if(argv[1] == "-umount"){
            cerrar_bib(argv[2]);
        }else{
            fprintf (stderr, "Unknown option `-%c'.\n", argv[3]);
        }

    }else if(argc == 4){
        if(argv[1] == "-create"){
            //fprintf ("Sintax:-create name flags\n");
            crear_bib(argv[2], argv[3]);

        }else if(argv[1] == "-mount"){
            abrir_bib(argv[2], argv[3]);

        }else if(argv[1] == "-mv"){
            incluir_comp(argv[2], argv[3]);

        }else if(argv[1] == "-ls"){
            listar_comps(argv[2], argv[3]);

        }else if(argv[1] == "-open"){
            abrir_comp(argv[2], argv[3]);

        }else if(argv[1] == "-delete"){
            eliminar_comp(argv[2], argv[3]);

        } else {
            fprintf (stderr, "Unknown option `-%c'.\n", argv[3]);
        }

    }else if(argc == 5){
        if(argv[1] == "-print"){
            leer_comp(argv[2], argv[3], argv[4]);
        }else{
            fprintf (stderr, "Unknown option `-%c'.\n", argv[3]);
        }
    }else{
        fprintf (stderr, "Unknown option `-%c'.\n", argv[3]);
    }

    return var;
}
