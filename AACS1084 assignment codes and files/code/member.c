#include "member.h"

Member member[MAX_member];
int num_member = 0;
int current_member_index = -1;
int memberMenu() {
	void saveMember();
	void loadMember();
	void MemberID();
	void MemberRegister();
	void Memberlogin();
	int MemberResetPassword();
	void MemberBookTicket();
	void MemberDeleteBooking();
	void MemberBookingHistory();
	void MemberBookingReport();
	void Memberlogout();
	int select;
	printf("Member Information Module\n");
	printf("-------------------------\n");
	do {
		printf("\n1.Member Register\n");
		printf("2.Member Login\n");
		printf("3.Recover Password\n");
		printf("4.Book Ticket\n");
		printf("5.Delete Booking\n");
		printf("6.Book History\n");
		printf("7.Book Report\n");
		printf("8.Member Logout\n");
		printf("9.Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &select);

		switch (select) {
		case 1:
			MemberRegister();
			break;
		case 2:
			Memberlogin();
			break;
		case 3:
			MemberResetPassword();
			break;
		case 4:
			MemberBookTicket();
			break;
		case 5:
			MemberDeleteBooking();
			break;
		case 6:
			MemberBookingHistory();
			break;
		case 7:
			MemberBookingReport();
			break;
		case 8:
			Memberlogout();
			break;
		case 9:
			printf("Exiting...\n");
			break;
		default:
			printf("Invalid choice.Please try again.\n");
			break;
		}
	} while (select != 9);

	loadMember();

	return 0;
}

void saveMember() {
	FILE* fptr = fopen("listmember.dat", "wb");
	if (fptr == NULL) {
		printf("Error: Unable to open file for writing.\n");
		return;
	}
	fwrite(&num_member, sizeof(int), 1, fptr);
	fwrite(member, sizeof(Member), num_member, fptr);
	fclose(fptr);
}

void loadMember() {
	FILE* fptr = fopen("listmember.dat", "rb");
	if (fptr == NULL) {
		printf("Error: Unable to open file for reading.\n");
		return;
	}
	fread(&num_member, sizeof(int), 1, fptr);
	fread(member, sizeof(Member), num_member, fptr);
	fclose(fptr);
}

int next_member_number = 1;

void MemberID(char* member_id) {
	sprintf(member_id, "M%04d", next_member_number++);
}

void MemberRegister() {
	system("cls");
	if (num_member >= MAX_member) {
		printf("Cannot add more members. Member is full already.\n");
		return;
	}
	MemberID(member[num_member].member_id);
	printf("Your Member ID: %s\n", member[num_member].member_id);
	printf("Enter username: ");
	scanf("%s", member[num_member].login);
	printf("Enter password: ");
	scanf("%s", member[num_member].password);
	printf("Enter contact details: ");
	scanf("%s", member[num_member].contact_details);
	printf("Member addded successfully!\n");
	num_member++;

	saveMember();
}

void Memberlogin() {
	system("cls");
	char member_id[6];
	char password[50];
	int attempts = 0;

	while (attempts < MAX_login) {
		printf("Enter Member ID: ");
		scanf("%s", member_id);
		printf("Enter password: ");
		scanf("%s", password);

		int i;
		for (i = 0; i < num_member; i++) {
			if (strcmp(member_id, member[i].member_id) == 0 &&
				strcmp(password, member[i].password) == 0) {
				printf("Login successful, Welcome!\n");
				current_member_index = i;
				return;
			}
		}
		printf("Invalid Member ID Or Password. Please Try again.\n");
		attempts++;
	}
	if (attempts == MAX_login) {
		printf("Maximum login attempts reached. Resetting Password...\n");
		if (MemberResetPassword() == 1) {
			printf("Password reset successfully!\n");
		}
		else {
			printf("Password reset failed!\n");
		}
	}
}

int MemberResetPassword() {
	system("cls");
	char member_id[6];
	printf("Enter your Member ID to reset password: ");
	scanf("%s", member_id);

	int i;
	for (i = 0; i < num_member; i++) {
		if (strcmp(member_id, member[i].member_id) == 0) {
			printf("Enter new password: ");
			scanf("%s", member[i].password);
			printf("Enter reset successfully!\n");
			saveMember();
			return 1;
		}
	}
	printf("No member found with the provided member id.\n");
	return 0;
}

void MemberBookTicket() {
	system("cls");
	if (current_member_index == -1) {
		printf("Please login first to book a ticket.\n");
		return;
	}

	Member* current_member = &member[current_member_index];

	if (current_member->num_bookings >= MAX_ticket) {
		printf("Cannot book more tickets. Maximum tickets reached.\n");
		return;
	}

	printf("Enter destination: ");
	scanf("%s", current_member->booking_history[current_member->num_bookings].destination);
	printf("Enter booking date: ");
	scanf("%s", current_member->booking_history[current_member->num_bookings].booking_date);
	printf("Enter ticket ID: ");
	scanf("%s", current_member->booking_history[current_member->num_bookings].ticket_number);
	printf("Enter ticket price: ");
	scanf("%f", &current_member->booking_history[current_member->num_bookings].ticket_price);

	printf("Ticket booked successfully!\n");
	current_member->num_bookings++;
	saveMember();
}


void MemberDeleteBooking() {
	system("cls");
	if (current_member_index == -1) {
		printf("Please log in first to delete a booking.\n");
		return;
	}

	Member* current_member = &member[current_member_index];
	if (current_member->num_bookings == 0) {
		printf("No bookings found for the member.\n");
		return;
	}

	char ticket_number[20];
	printf("Enter ticket ID to delete booking: ");
	scanf("%s", ticket_number);

	for (int j = 0; j < current_member->num_bookings; j++) {
		if (strcmp(ticket_number, current_member->booking_history[j].ticket_number) == 0) {
			for (int k = j; k < current_member->num_bookings - 1; k++) {
				strcpy(current_member->booking_history[k].destination, current_member->booking_history[k + 1].destination);
				strcpy(current_member->booking_history[k].booking_date, current_member->booking_history[k + 1].booking_date);
				strcpy(current_member->booking_history[k].ticket_number, current_member->booking_history[k + 1].ticket_number);
				current_member->booking_history[k].ticket_price = current_member->booking_history[k + 1].ticket_price;
			}
			current_member->num_bookings--;
			printf("Booking deleted successfully!\n");
			saveMember();
			return;
		}
	}

	printf("No booking found with the provided ticket number.\n");
}

void MemberBookingHistory() {
	system("cls");
	if (current_member_index == -1) {
		printf("Please log in first to view booking history.\n");
		return;
	}

	Member* current_member = &member[current_member_index];

	if (current_member->num_bookings == 0) {
		printf("No booking history found for the member.\n");
		return;
	}

	printf("Booking History for Member: %s\n", current_member->member_id);
	printf("------------------------------------------------\n");
	printf("%-20s%-15s%-20s%-20s\n", "Destination", "Booking Date", "Ticket Number", "Ticket Price");
	printf("------------------------------------------------\n");
	for (int j = 0; j < current_member->num_bookings; j++) {
		printf("%-20s%-15s%-20s%-20.2f\n", current_member->booking_history[j].destination,
			current_member->booking_history[j].booking_date,
			current_member->booking_history[j].ticket_number,
			current_member->booking_history[j].ticket_price);
	}
}

void MemberBookingReport() {
	system("cls");
	printf("Booking Report for All Members:\n");
	printf("------------------------------------------------\n");
	printf("%-20s%-20s%-20s%-20s%-15s\n", "Member", "Destination", "Booking Date", "Ticket Number", "Ticket Price");
	printf("------------------------------------------------\n");

	float total_amount = 0;
	for (int i = 0; i < num_member; i++) {
		if (member[i].num_bookings == 0) {
			continue;
		}

		for (int j = 0; j < member[i].num_bookings; j++) {
			printf("%-20s%-20s%-20s%-20s%-15.2f\n", member[i].member_id, member[i].booking_history[j].destination,
				member[i].booking_history[j].booking_date, member[i].booking_history[j].ticket_number,
				member[i].booking_history[j].ticket_price);
			total_amount += member[i].booking_history[j].ticket_price;
		}
	}
	printf("\nTotal Amount for All Members: %.2f\n", total_amount);
}

void Memberlogout() {
	system("cls");
	current_member_index = -1;
	printf("Logged out successfully!\n");
}