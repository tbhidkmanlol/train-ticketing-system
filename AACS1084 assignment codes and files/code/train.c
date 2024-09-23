#include "train.h"

int trainMenu() {
    Train schedule[MAX_SCHEDULE_ENTRIES];
    int num_trains = 0;
    int selection;

    do {
        display_menu();
        printf("Enter a number to continue: ");
        scanf("%d", &selection);

        switch (selection) {
        case 1:
            add_train(schedule, &num_trains);
            break;
        case 2:
            search_train(schedule, num_trains);
            break;
        case 3:
            modify_train(schedule, num_trains);
            break;
        case 4:
            display_schedule(schedule, num_trains);
            break;
        case 5:
            delete_train(schedule, &num_trains);
            break;
        case 6:
            generate_report(schedule, num_trains);
            break;
        case 7:
            save_schedule(schedule, num_trains);
            printf("Exiting program.\n");
            break;
        default:
            printf("\nInvalid selection. Please enter a valid number.\n\n");
            break;
        }
    } while (selection != 7);

    return 0;
}

void display_menu() {
    printf("\n=== Train Schedule Management System ===\n");
    printf("1. Add a train\n");
    printf("2. Search for a train\n");
    printf("3. Modify train details\n");
    printf("4. Display schedule\n");
    printf("5. Delete a train\n");
    printf("6. Generate report\n");
    printf("7. Save & Exit\n");
}

void add_train(Train schedule[], int* num_trains) {
    if (*num_trains >= MAX_SCHEDULE_ENTRIES) {
        printf("Schedule is full. Cannot add more trains.\n");
        return;
    }

    printf("\nEnter train details:\n");
    printf("Train Number: ");
    scanf("%d", &schedule[*num_trains].train_number);
    printf("Train Name: ");
    scanf("%49s", schedule[*num_trains].train_name);
    printf("Departure Time: ");
    scanf("%9s", schedule[*num_trains].departure_time);
    printf("Arrival Time: ");
    scanf("%9s", schedule[*num_trains].arrival_time);
    printf("Source: ");
    scanf("%49s", schedule[*num_trains].source);
    printf("Destination: ");
    scanf("%49s", schedule[*num_trains].destination);

    (*num_trains)++;
    printf("Train added successfully.\n");
    system("cls");
}

void search_train(Train schedule[], int num_trains) {
    int train_num;
    printf("Enter the train number to search: ");
    scanf("%d", &train_num);
    int found = 0;
    system("cls");

    for (int i = 0; i < num_trains; i++) {
        if (schedule[i].train_number == train_num) {
            printf("\nTrain Number: %d\nTrain Name: %s\nDeparture Time: %s\nArrival Time: %s\nSource: %s\nDestination: %s\n",
                schedule[i].train_number, schedule[i].train_name, schedule[i].departure_time,
                schedule[i].arrival_time, schedule[i].source, schedule[i].destination);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Train not found.\n");
}

void modify_train(Train schedule[], int num_trains) {
    int train_num;
    printf("Enter the train number to modify: ");
    scanf("%d", &train_num);
    int found = 0;
    system("cls");

    for (int i = 0; i < num_trains; i++) {
        if (schedule[i].train_number == train_num) {
            printf("Enter new train details:\n");
            printf("Train Number: ");
            scanf("%d", &schedule[i].train_number);
            printf("Train Name: ");
            scanf("%49s", schedule[i].train_name);
            printf("Departure Time: ");
            scanf("%9s", schedule[i].departure_time);
            printf("Arrival Time: ");
            scanf("%9s", schedule[i].arrival_time);
            printf("Source: ");
            scanf("%49s", schedule[i].source);
            printf("Destination: ");
            scanf("%49s", schedule[i].destination);

            printf("Train details modified successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Train not found.\n");
}

void display_schedule(Train schedule[], int num_trains) {
    printf("--------------------------------------------------------------------------------\n");
    printf("Train Number\tName\t\tDeparture Time\tArrival Time\tSource\t\tDestination\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_trains; i++) {
        printf("%-13d\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n",
            schedule[i].train_number, schedule[i].train_name, schedule[i].departure_time,
            schedule[i].arrival_time, schedule[i].source, schedule[i].destination);
    }
    system("pause");
    system("cls");
}

void delete_train(Train schedule[], int* num_trains) {
    int train_num;
    printf("Enter the train number to delete: ");
    scanf("%d", &train_num);
    int found = 0;
    system("cls");

    for (int i = 0; i < *num_trains; i++) {
        if (schedule[i].train_number == train_num) {
            found = 1;
            for (int j = i; j < *num_trains - 1; j++) {
                schedule[j] = schedule[j + 1];
            }
            (*num_trains)--;
            printf("Train deleted successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Train not found.\n");
}

void save_schedule(Train schedule[], int num_trains) {
    FILE* file = fopen("train_schedule.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d\n", num_trains);

    for (int i = 0; i < num_trains; i++) {
        fprintf(file, "%d,%s,%s,%s,%s,%s\n",
            schedule[i].train_number,
            schedule[i].train_name,
            schedule[i].departure_time,
            schedule[i].arrival_time,
            schedule[i].source,
            schedule[i].destination);
    }

    fclose(file);
    system("cls");
}

void load_schedule(Train schedule[], int* num_trains) {
    FILE* file = fopen("train_schedule.txt", "r");
    if (file == NULL) {
        printf("No existing schedule found.\n");
        return;
    }

    fscanf(file, "%d\n", num_trains);

    for (int i = 0; i < *num_trains; i++) {
        fscanf(file, "%d,%49[^,],%9[^,],%9[^,],%49[^,],%49[^\n]\n",
            &schedule[i].train_number,
            schedule[i].train_name,
            schedule[i].departure_time,
            schedule[i].arrival_time,
            schedule[i].source,
            schedule[i].destination);
    }

    fclose(file);
}

void generate_report(Train schedule[], int num_trains) {
    printf("\n=== Train Schedule Report ===\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Train Number\tName\t\tDeparture Time\tArrival Time\tSource\t\tDestination\n");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < num_trains; i++) {
        printf("%-13d\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n",
            schedule[i].train_number, schedule[i].train_name, schedule[i].departure_time,
            schedule[i].arrival_time, schedule[i].source, schedule[i].destination);
    }
}