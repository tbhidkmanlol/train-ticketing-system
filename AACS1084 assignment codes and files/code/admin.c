#include "admin.h"

int isLogin = 0; // track login status

int login(staff* loginStaff) {
	printf("\n=== Staff Information Module ===\n");
	char inputStaffId[11];
	char inputPassword[MAX_PASSWORD_LENGTH];
	int attempts = 0;

	while (attempts < MAX_LOGIN_ATTEMPTS) {
		printf("Enter Staff ID: ");
		scanf("%s", inputStaffId);
		printf("Enter Password: ");
		scanf("%s", inputPassword);

		// Check if input matches default staff ID and password
		if (strcmp(inputStaffId, DEFAULT_STAFF_ID) == 0 && strcmp(inputPassword, DEFAULT_PASSWORD) == 0) {
			printf("Login successful using default credentials!\n");
			strcpy(loginStaff->name, "Admin"); // Set the name to "Admin" for default login
			return 1;
		}

		FILE* fp = fopen("staff_info.bin", "rb");
		if (!fp) {
			printf("Error opening file.\n");
			return -1; // Return -1 on file error
		}

		staff tempStaff;
		// Read each staff record from the file
		while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
			// Check if the staff ID and password match
			if (strcmp(inputStaffId, tempStaff.staffid) == 0 && strcmp(inputPassword, tempStaff.password) == 0) {
				printf("Login successful!\n");
				strcpy(loginStaff->name, tempStaff.name); // Assign the logged-in staff's name
				fclose(fp);
				return 1;
			}
		}
		fclose(fp);

		printf("Invalid Staff ID or password. Please try again.\n");
		attempts++;
	}

	// Display password recovery hint after three failed attempts
	printf("Maximum login attempts reached. Initiating password recovery...\n");
	passwordRecovery(inputStaffId);
	attempts = 0; // Reset attempts counter
	return 0; // Return 0 for unsuccessful login
}

void passwordRecovery(const char* staffId) {
	FILE* fp = fopen("staff_info.bin", "rb");
	if (!fp) {
		printf("Error opening file.\n");
		return;
	}

	staff tempStaff;
	// Read each staff record from the file
	while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
		// Check if the input staff ID matches
		if (strcmp(staffId, tempStaff.staffid) == 0) {
			printf("Your password recovery hint: %s\n", tempStaff.password_recovery);
			fclose(fp);
			return;
		}
	}
	fclose(fp);

	printf("Staff ID not found. Please try again.\n");
}

void signout() {
	isLogin = 0; //login status to false
	printf("logged out successfully.\n");
	system("cls");
}

void displayMenu(const char* staffName) {
	printf("\n=========================\n");
	printf("  Welcome, %s!\n", staffName);
	printf("=========================\n");
	printf("1. Add Staff\n");
	printf("2. Search Staff\n");
	printf("3. Modify Staff\n");
	printf("4. Display Staff\n");
	printf("5. Delete Staff\n");
	printf("6. Report Staff\n");
	printf("7. Sign Out\n");
	printf("8. Exit\n");
	printf("Please enter your choice here (1-8): ");
}

int staffMenu() {
	void displayMenu(const char* staffName);
	void passwordRecovery(char* staffId);
	int login(staff * loginStaff);
	void signout();
	int choice = 0;
	staff loginStaff;
	int loginResult; // Variable to store the result of login function

	do {
		if (!isLogin) {
			loginResult = login(&loginStaff); // Attempt to login
			if (loginResult == 0) {
				printf("Invalid Staff ID or password. Please try again.\n");
				continue; // Loop back to login screen
			}
			else if (loginResult == -1) {
				printf("Exiting...\n");
				break; // Exit the program on file error
			}
			isLogin = 1; // Set login status to true
			displayMenu(loginStaff.name); // Pass the staff's name to displayMenu
		}
		scanf("%d", &choice);
		switch (choice) {
		case 1: addStaff();
			break;
		case 2: searchStaff();
			break;
		case 3: modifyStaff();
			break;
		case 4: displayStaff();
			break;
		case 5: deleteStaff();
			break;
		case 6: reportStaff();
			break;
		case 7: printf("Signing out...\n");
			isLogin = 0; // Reset login status
			break;
		case 8: printf("Exiting...\n");
			system("cls");
			break;
		default: printf("Invalid choice. Please try again.\n");
			while (getchar() != '\n'); // Clear input buffer
			break;
		}

		if (isLogin && choice != 8) {
			displayMenu(loginStaff.name);
		}

	} while (choice != 8);

	return 0;
}

void addStaff() {
	staff newStaff;
	char choice;

	FILE* fp = fopen("staff_info.bin", "ab+");
	if (!fp) {
		printf("Error opening file.\n");
		exit(-1);
	}

	do {
		int isUnique;
		do {
			isUnique = 1; // Assume the ID is unique until a duplicate is found
			system("cls");
			printf(" + ---------------------- - + \n");
			printf(" |   add staff poggers    | \n");
			printf(" + ---------------------- - + \n");

			printf("Enter Staff ID: ");
			scanf(" %s", newStaff.staffid);

			// Check for duplicate staff ID
			staff tempStaff;
			rewind(fp); // Go back to the start of the file
			while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
				if (strcmp(tempStaff.staffid, newStaff.staffid) == 0) {
					printf("Warning: Staff ID already exists. Please enter a unique ID.\n");
					printf("Press enter to continue.\n");
					isUnique = 0; // Set the flag to indicate a duplicate was found
					// Clear the input buffer
					int c;
					while ((c = getchar()) != '\n' && c != EOF);

					getchar(); // Wait for the user to press enter
					break; // Break the inner loop
				}
			}
		} while (!isUnique); // Repeat the inner loop if a duplicate was found

		// Continue with the rest of the staff details
		printf("Enter Name: ");
		scanf(" %[^\n]", newStaff.name);

		printf("Enter Password: ");
		scanf(" %s", newStaff.password);

		printf("Enter Password Recovery: ");
		scanf(" %[^\n]", newStaff.password_recovery);

		printf("Enter Position: ");
		scanf(" %[^\n]", newStaff.position);

		fwrite(&newStaff, sizeof(staff), 1, fp);

		printf("Do you want to add another staff? (y/n): ");
		scanf(" %c", &choice);

	} while (choice == 'y' || choice == 'Y');

	fclose(fp);
	printf("Staff added successfully.\n");
}

void searchStaff() {
	FILE* fp;
	staff tempStaff;
	char searchID[11];
	int found = 0;
	fp = fopen("staff_info.bin", "rb");
	if (fp == NULL) {
		printf("Error opening file.\n");
		exit(-1);
	}
	system("cls");
	printf("Enter Staff ID to search: ");
	scanf("%s", searchID);

	// Clear the input buffer
	while (getchar() != '\n');

	while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
		if (strcmp(tempStaff.staffid, searchID) == 0) {
			printf(" + -------------- + \n");
			printf(" |  staff found   | \n");
			printf(" + -------------- + \n");
			printf("Staff ID\tName\t\tPassword Recovery\tPosition\n");
			printf("--------------------------------------------------------------------------------\n");
			printf("%-10s\t%-15s\t%-20s\t%-20s\n\n", tempStaff.staffid, tempStaff.name, tempStaff.password_recovery, tempStaff.position);
			found = 1;
			break;
		}
	}

	if (!found) {
		printf(" + -----------------  + \n");
		printf(" |  staff not found   | \n");
		printf(" |  please key in the | \n");
		printf(" |  correct staff id. | \n");
		printf(" + -----------------  + \n");
		int d;
		printf("Press Enter to continue...");
		while ((d = getchar()) != '\n' && d != EOF);
		getchar();
	}

	fclose(fp);
}

void modifyStaff() {
	FILE* fp;
	FILE* tempFile;
	staff tempStaff;
	char searchID[11];
	int found = 0;
	fp = fopen("staff_info.bin", "r+b");
	tempFile = fopen("temp.bin", "wb");
	if (fp == NULL || tempFile == NULL) {
		printf("Error opening file.\n");
		return;
	}
	system("cls");
	printf("Enter Staff ID to modify: ");
	scanf("%s", searchID);

	while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
		if (strcmp(tempStaff.staffid, searchID) == 0) {
			int choice;
			do {
				printf("1. Modify Password and Password Recovery Hint\n");
				printf("2. Modify Position\n");
				printf("Enter your choice: ");
				if (scanf("%d", &choice) != 1) { // Check if input is a valid integer
					printf("Invalid choice. Please enter a valid number.\n");
					system("cls");
					while (getchar() != '\n'); // Clear input buffer
					continue;
				}
				switch (choice) {
				case 1:
					printf("Enter New Password: ");
					scanf(" %s", tempStaff.password);
					printf("Enter New Password Recovery Hint: ");
					scanf(" %[^\n]", tempStaff.password_recovery);
					found = 1;
					break;
				case 2:
					printf("Enter New Position: ");
					scanf(" %[^\n]", tempStaff.position);
					found = 1;
					break;
				default:
					printf("Invalid choice. Please try again.\n");
					system("cls");
					break;
				}
			} while (choice != 1 && choice != 2); // Loop until a valid choice (1 or 2) is entered
		}
		fwrite(&tempStaff, sizeof(staff), 1, tempFile);
	}

	if (!found) {
		printf(" + -----------------  + \n");
		printf(" |  staff not found   | \n");
		printf(" |  please key in the | \n");
		printf(" |  correct staff id. | \n");
		printf(" + -----------------  + \n");
		int d;
		printf("Press Enter to continue...");
		while ((d = getchar()) != '\n' && d != EOF);
		getchar();
		system("cls");
	}
	else {
		printf("Staff information modified successfully.\n");
		int d;
		printf("Press Enter to continue...");
		while ((d = getchar()) != '\n' && d != EOF);
		getchar();
		system("cls");
	}

	fclose(fp);
	fclose(tempFile);

	remove("staff_info.bin");
	rename("temp.bin", "staff_info.bin");
}

void displayStaff() {
	FILE* fp = fopen("staff_info.bin", "rb");
	if (!fp) {
		printf("Error opening file.\n");
		return;
	}

	staff tempStaff;
	system("cls");
	printf(" + ------------------ + \n");
	printf(" |    wow guys look   | \n");
	printf(" |  staff information | \n");
	printf(" |       no way       | \n");
	printf(" + ------------------ + \n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Staff ID\tName\t\tPassword\tPassword Recovery\tPosition\n");
	printf("--------------------------------------------------------------------------------\n");
	while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
		printf("%-10s\t%-15s\t%-15s\t%-20s\t%-20s\n\n", tempStaff.staffid, tempStaff.name, tempStaff.password,
			tempStaff.password_recovery, tempStaff.position);

	}
	fclose(fp);
}

void deleteStaff() {
	char searchId[11];
	FILE* fp = fopen("staff_info.bin", "r+b");
	if (!fp) {
		printf("Error opening file.\n");
		return;
	}

	system("cls");
	printf("Enter Staff ID to delete: ");
	scanf("%s", searchId);

	staff tempStaff;
	FILE* tempFile = fopen("temp.bin", "wb");
	if (!tempFile) {
		printf("Error creating temporary file.\n");
		fclose(fp);
		return;
	}

	int found = 0;
	while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
		if (strcmp(tempStaff.staffid, searchId) == 0) {
			found = 1;
			printf("Staff with ID %s has been deleted.\n", searchId);
			int d;
			printf("Press Enter to continue...");
			while ((d = getchar()) != '\n' && d != EOF);
			getchar();
			system("cls");
		}
		else {
			fwrite(&tempStaff, sizeof(staff), 1, tempFile); // Write to temporary file if not the one to be deleted
		}
	}

	fclose(fp);
	fclose(tempFile);

	remove("staff_info.bin"); // Remove original file
	rename("temp.bin", "staff_info.bin"); // Rename temporary file to original name

	if (!found) {
		printf(" + -----------------  + \n");
		printf(" |  staff not found   | \n");
		printf(" |  please key in the | \n");
		printf(" |  correct staff id. | \n");
		printf(" + -----------------  + \n");
		int d;
		printf("Press Enter to continue...");
		while ((d = getchar()) != '\n' && d != EOF);
		getchar();
	}
}

void reportStaff() {
	FILE* fp = fopen("staff_info.bin", "rb");
	if (!fp) {
		printf("Error opening file.\n");
		return;
	}

	staff tempStaff;
	int staffCount = 0;

	system("cls");
	printf("Staff ID\tName\t\tPosition\n");
	printf("--------------------------------------------------\n");
	while (fread(&tempStaff, sizeof(staff), 1, fp) != 0) {
		printf("%-10s\t%-15s\t%-20s\n", tempStaff.staffid, tempStaff.name, tempStaff.position);
		staffCount++;
	}
	printf("--------------------------------------------------\n");
	printf("Total number of staff members: %d\n", staffCount);

	fclose(fp);
}