//Grzegorz Olszewski
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Result{
    int month;
    int day;
    int h_programming;
    int h_reading;
    int h_doing_exercises;
} Result;

typedef struct Student{
    char name[30];
    Result results[366];
} Student;

 typedef struct CorrectCommends{
    char quit[30];
    char newStudent[30];
    char add[30];
    char plot[30];
    char show[30];
} CorrectCommends;



void createDatabaseIfDoesntExist();
void addNewStudent();
void addStudentToDatabase(char name[30]);
void changeStudent();
void addHoursToRecord(char name[], int month, int day, int h_programming, int h_doing_exercises, int h_reading);
void getCommand(char *command);
Student *createStudent(char name[30]);
int printDatabase();
bool alreadyExisted(char name[]);
void plot();

