#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable: 4996)

#include "admin.h"
#include "member.h"
#include "ticket.h"
#include "train.h"

void displayMainMenu() {

	printf("\n + ----------------------------------  +\n");
	printf(" |   Welcome to Train Booking System   |\n");
	printf(" + ----------------------------------- +\n");


	printf("1. Staff\n");
	printf("2. Member\n");
	printf("3. Ticket\n");
	printf("4. Train\n");
	printf("5. Exit\n");
	printf("====================================\n");
	printf("Please select your choice (1-5): ");
}

int main() {
	int choice;
	do {
		displayMainMenu();
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			staffMenu();
			break;
		case 2:
			memberMenu();
			break;
		case 3:
			ticketMenu();
			break;
		case 4:
			trainMenu();
			break;
		case 5:
			printf("Exiting...\n");
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			break;
		}
	} while (choice != 5);

	system("pause");
}
