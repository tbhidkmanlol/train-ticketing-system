#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

#define MAX_PASSWORD_LENGTH 20
#define MAX_LOGIN_ATTEMPTS 3

// default staff id and password for demo purposes
#define DEFAULT_STAFF_ID "admin"
#define DEFAULT_PASSWORD "admin123"

typedef struct {
	char staffid[11], name[50],
		password[MAX_PASSWORD_LENGTH], password_recovery[50], position[50];
} staff;

//function declaration
void addStaff();
void searchStaff();
void modifyStaff();
void displayStaff();
void deleteStaff();
void reportStaff();
void displayMenu(const char* staffname);
void passwordRecovery(char* staffid);
int login(staff* loginstaff);
void signout();
int staffMenu();


