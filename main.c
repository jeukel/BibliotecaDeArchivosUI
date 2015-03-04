#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../BibliotecaDeArchivos/hard_drive.h"
#define MAX_SIZE_IN_BUFFER 96
#define EXIT 'exit'

char command;
char command_buffer[MAX_SIZE_IN_BUFFER];
int char_count;
int var;

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

int main(int argc, char *argv[])
{
//    presentation();

    var = 0;
    if (argc == 3){
        if(!strcmp (argv[1], "umount")){
            umount((int)*argv[2]);

        }else if(!strcmp (argv[1],"ls")){
            listComp(argv[2]);

        }else{
            fprintf (stderr, "Unknown option `-%c'.\n", argc);
        }

    }else if(argc == 4){
        if(!strcmp (argv[1],"create")){
            //create(argv[2], argv[3]);

        }else if(!strcmp (argv[1], "mount")){
            //mount(argv[2], (int*)argv[3]);

        }else if(!strcmp (argv[1],"open")){
            //openc(argv[2], argv[3]);

        }else if(!strcmp (argv[1],"del")){
            //del(argv[2], argv[3]);

        } else {
            fprintf (stderr, "Unknown option `-%c'.\n", argc);
        }

    }else if(argc == 5){
        if(!strcmp (argv[1],"print")){
            //print(argv[2], argv[3], argv[4]);

        }else if(!strcmp (argv[1],"export")){
            //exportFile(argv[2], argv[3], argv[4]);

        }else if(!strcmp (argv[1],"import")){
            //import(argv[2], argv[3], argv[4]);

        }else{
            fprintf (stderr, "Unknown option `-%c'.\n", argc);
        }

    }else{
        fprintf (stderr, "Unknown option `-%c'.\n", argc);
    }

    return var;
}
