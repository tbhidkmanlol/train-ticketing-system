#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)

#define MAX_TRAIN_NAME_LENGTH 50
#define MAX_SCHEDULE_ENTRIES 100

typedef struct {
    int train_number;
    char train_name[MAX_TRAIN_NAME_LENGTH];
    char departure_time[10];
    char arrival_time[10];
    char source[50];
    char destination[50];
} Train;

void display_menu();
void add_train(Train schedule[], int* num_trains);
void search_train(Train schedule[], int num_trains);
void modify_train(Train schedule[], int num_trains);
void display_schedule(Train schedule[], int num_trains);
void delete_train(Train schedule[], int* num_trains);
void save_schedule(Train schedule[], int num_trains);
void load_schedule(Train schedule[], int* num_trains);
void generate_report(Train schedule[], int num_trains);
int trainMenu();