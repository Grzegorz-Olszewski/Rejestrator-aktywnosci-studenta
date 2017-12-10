
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
//Grzegorz Olszewski
void createDatabaseIfDoesntExist(){
    FILE *p;
    if(!(p = fopen("database", "rb"))){
        p = fopen("database", "wb");
    }
    fclose(p);
}
Student *createStudent(char name[30]){
    Student *ptr = (Student*)malloc(sizeof(Student));
    time_t t;
    srand((unsigned) time(&t));
    for(int i = 0; i < 30; i++){
        ptr->name[i] = name[i];
    }
    int count = 0;
    for(int i = 1; i <= 12; i++){
        if(i==2){
            for(int k = 1; k <= 28; k++){
                ptr->results[count].month = i;
                ptr->results[count].day = k;
                ptr->results[count].h_doing_exercises= rand() % 5 ;
                ptr->results[count].h_programming=rand() % 5;
                ptr->results[count].h_reading=rand() % 5;
                count++;
            }
        }
        else if(i==1 || i==3 || i==5  || i==7 || i==8 || i==10 || i==12){
            for(int k = 1; k <= 31; k++){
                ptr->results[count].month = i;
                ptr->results[count].day = k;
                ptr->results[count].h_doing_exercises=rand() % 5;
                ptr->results[count].h_programming=rand() % 5;
                ptr->results[count].h_reading=rand() % 5;
                count++;
            }
        }
        else if(i==4 || i==6 || i==9  || i==11 ){
            for(int k = 1; k <= 30; k++){
                ptr->results[count].month = i;
                ptr->results[count].day = k;
                ptr->results[count].h_doing_exercises=rand() % 5;
                ptr->results[count].h_programming=rand() % 5;
                ptr->results[count].h_reading=rand() % 5;
                count++;
            }
        }
    }

    return ptr;
}
void getCommand(char *command){
    printf("Commands:\n");
    printf("1.) quit - to quit program\n");
    printf("2.) new - to add new student\n");
    printf("3.) add - to add new record to existing student\n");
    printf("4.) plot - to plot a graph\n");
    printf("5.) show - to show saved students\n");
    char *result;
    result = fgets(command, 30, stdin);
    if(result==NULL){
        printf("Something went wrong.");
        exit(0);
    }
    fflush(stdin);
}
void addNewStudent(){
    char name[30];
    printf("Please, give me a name of new student.\n");
    while(true){
            char *result;
            result = fgets(name, 30, stdin);
            if(result==NULL){
                printf("Something went wrong.");
                exit(0);
            }
            for(int i = strlen(name)-1; i < 30; i++){
                name[i] = ' ';
            }
            char shortName[30];
            for(int i = 0; i < 30; i++){
                if(!isspace(name[i])){
                    shortName[i] = name[i];
                }

            }
            if(alreadyExisted(name)){
                printf("Student %s already exist. Please give me different name.\n", shortName);
                fflush(stdin);
            }else{
                printf("Student %s was added.\n",shortName);
                addStudentToDatabase(name);
                fflush(stdin);
                break;
            }

        }

}
void addStudentToDatabase(char name[30]){
    FILE *p  = fopen("database", "ab");
    Student stud = *(createStudent(name));
    fwrite(&stud, sizeof(stud), 1, p);
    fclose(p);
}



void changeStudent(){
    char name[30];
    char buffer[30];
    char shortName[30];
    printf("Please, give me a name of a student.\n");
    while(true){
        char *result;
        result = fgets(buffer, 30, stdin);
        if(result==NULL){
            printf("Something went wrong.");
            exit(0);
        }
        for(int i = strlen(buffer)-1; i < 30; i++){
            buffer[i] = ' ';
        }
        for(int i = 0; i < 30; i++){
            if(!isspace(buffer[i])){
                shortName[i] = buffer[i];
            }
        }
        if(alreadyExisted(buffer)){
            printf("Student %s found!\n", shortName);
            for(int i = 0; i < 30; i++){
                name[i] = buffer[i];
            }
            fflush(stdin);
            break;
        }else{
            printf("Student %s not found.\n Try again\n",shortName);
            for(int i = 0; i < 30; i++){
                buffer[i] = ' ';
            }
            fflush(stdin);

        }
    }
    int month;
    printf("Tell me the month of a day you want to change.\n");
    int result;
    result =  scanf("%d",&month);
    if(result!=1){
        printf("Something went wrong.");
        exit(0);
    }
    int day;
    printf("Tell me the number of a day.\n");
     result = scanf("%d",&day);
    if(result!=1){
        printf("Something went wrong.");
        exit(0);
    }
    int h_programming;
    printf("How many hours of programming?\n");
    result = scanf("%d",&h_programming);
    if(result!=1){
        printf("Something went wrong.");
        exit(0);
    }
    int h_doing_exercises;
    printf("How many hours of doing exercises?\n");
    result = scanf("%d", &h_doing_exercises);
    if(result!=1){
        printf("Something went wrong.");
        exit(0);
    }
    int h_reading;
    printf("How many hours of reading?\n");
    result = scanf("%d", &h_reading);
    if(result!=1){
        printf("Something went wrong.");
        exit(0);
    }
    printf("%d.%d.2017\n",day, month);
    printf("hours of programming: %d\n", h_programming);
    printf("hours doing exercises: %d\n", h_doing_exercises);
    printf("hours reading: %d\n\n",h_reading);
    addHoursToRecord(name, month, day, h_programming, h_doing_exercises, h_reading);
}

void addHoursToRecord(char name[], int month, int day, int h_programming, int h_doing_exercises, int h_reading){
    FILE *p = fopen("database", "r+b");
    Student *stud = (Student*)malloc(sizeof(Student));
    do{
        int result = fread(stud, sizeof(Student), 1, p);
        if(result!=1){
            printf("Something went wrong.");
            exit(0);
        }
        if(strncmp(stud->name, name, 30)==0){
            break;
        }

    } while(!feof(p));
    int count = day-1;
    for(int i = 1; i < month; i++){
        if(i==2){
            count+=28;
        }
        else if(i==1 || i==3 || i==5  || i==7 || i==8 || i==10 || i==12){
            count+=31;
        }
        else if(i==4 || i==6 || i==9  || i==11 ){
            count+=30;
        }
    }
    fseek(p, -(sizeof(Student)), SEEK_CUR );
    stud->results[count].h_programming = h_programming;
    stud->results[count].h_doing_exercises = h_doing_exercises;
    stud->results[count].h_reading = h_reading;

    fwrite(stud, sizeof(Student), 1, p);
    fclose(p);
}

bool alreadyExisted(char name[]){
    FILE *p = fopen("database", "rb");
    Student *buffer = (Student*)malloc(sizeof(Student));
    do{
        int result = fread(buffer, sizeof(Student), 1, p);
        if(result<0){
            printf("Something went wrong.");
            exit(0);
        }
        if(strncmp(buffer->name, name, 30)==0){
            fclose(p);
            return true;
        }

    } while(!feof(p));

    fclose(p);
    return false;
}
int printDatabase(){
    FILE *p;
    Student stud;
    p = fopen("database", "rb");
    printf("In database, we have following students:\n\n");
    while(fread(&stud, sizeof(Student), 1, p) != 0){
        printf("Name: %s\n", stud.name);
    }
    fclose(p);
    return 0;
}

void plot(){
    char name[30];
    char buffer[30];
    char shortName[30];
    printf("Please, give me a name of a student.\n");
    while(true){
        char *result;
        result = fgets(buffer, 30, stdin);
        if(result==NULL){
            printf("Something went wrong.");
            exit(0);
        }
        for(int i = strlen(buffer)-1; i < 30; i++){
            buffer[i] = ' ';
        }

        for(int i = 0; i < 30; i++){
            if(!isspace(buffer[i])){
                shortName[i] = buffer[i];
            }
        }
        if(alreadyExisted(buffer)){
            printf("Student %s found!\n", shortName);
            for(int i = 0; i < 30; i++){
                name[i] = buffer[i];
            }
            fflush(stdin);
            break;
        }else{
            printf("Student %s not found.\n Try again\n",shortName);
            for(int i = 0; i < 30; i++){
                buffer[i] = ' ';
            }
            fflush(stdin);
        }

    }
    FILE *p = fopen("database", "r+b");
    Student *stud = (Student*)malloc(sizeof(Student));
    do{
        int result = fread(stud, sizeof(Student), 1, p);
         if(result!=1){
            printf("Something went wrong.");
            exit(0);
        }
        if(strncmp(stud->name, name, 30)==0){
            break;
        }

    } while(!feof(p));
    fclose(p);

    printf("What you want to plot?\n");
    int answer;
    while(true){
        printf("Type 1 to plot a graph of hours of programming in consecutive months.\n");
        printf("Type 2 to plot a graph of doing exercises in consecutive months.\n");
        printf("Type 3 to plot a graph of reading in consecutive months.\n");
        int result = scanf("%d", &answer);
         if(result!=1){
            printf("Something went wrong.");
            exit(0);
        }
        if(answer == 1 || answer == 2 || answer == 3){
            break;
        }else{
            printf("Please use number from 1 to 3.\n");
        }
    }

    int sums[13];
    for(int i = 0 ; i < 13; i++){
        sums[i]=0;
    }
    if(answer == 1){
        for(int i = 0; i < 365; i++){
            sums[(stud->results[i].month)-1]+=stud->results[i].h_programming;
        }
    }
    else if(answer == 2){
        for(int i = 0; i < 365; i++){
            sums[(stud->results[i].month)-1]+=stud->results[i].h_doing_exercises;
        }
    }
    else if(answer == 3){
        for(int i = 0; i < 365; i++){
            sums[(stud->results[i].month)-1]+=stud->results[i].h_reading;
        }
    }
    FILE *p2=fopen("data.txt", "w");
    for(int i = 0; i < 12; i++){
        fprintf(p2, "%d %d \n", i+1, sums[i]);
    }
    fclose(p2);
    int result = system("gnuplot -p 'script.gp'");
     if(result==-1){
            printf("Something went wrong.");
            exit(0);
        }
}



