#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>
#include <stdbool.h>
//Grzegorz Olszewski
CorrectCommends AvailableCommands = {
    {'q','u','i','t',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' '},
    {'n','e','w',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' '},
    {'a','d','d',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' '},
    {'p','l','o','t',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' '},
    {'s','h','o','w',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ', ' '}
};

int main(){

    createDatabaseIfDoesntExist();
    char command[30];
    bool greeting = true;
    bool nonValidCommand = false;
    while(true){

        if(greeting){
            printf("Hi, what can I do for you?\n");
            greeting = false;
        }
        else if(nonValidCommand){
            printf("\n\nThis isn't a valid command.\n");
            nonValidCommand= false;
        }
        else{
            printf("\n\nWhat else can I do for you?\n");
        }
        getCommand(command);
        for(int i = strlen(command)-1; i < 30; i++){
            command[i] = ' ';
        }

        if(strncmp(command, AvailableCommands.quit, 30) == 0){
            break;
        }
        else if(strncmp(command, AvailableCommands.newStudent, 30) == 0){
            addNewStudent();
        }
        else if(strncmp(command,AvailableCommands.add, 30) == 0){
            changeStudent();
        }
        else if(strncmp(command,AvailableCommands.plot, 30) == 0){
            plot();
        }
        else if(strncmp(command,AvailableCommands.show, 30) == 0){
            printDatabase();
        }
        else{
            nonValidCommand= true;
        }
    }
}


