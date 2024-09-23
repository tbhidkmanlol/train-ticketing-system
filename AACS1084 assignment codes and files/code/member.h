#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
#define MAX_member 100
#define MAX_ticket 10
#define MAX_login 3

typedef struct {
	char destination[100];
	char booking_date[20];
	char ticket_number[20];
	float ticket_price;
}TicketBooking;

typedef struct {
	char member_id[6];
	char login[50];
	char password[50];
	char contact_details[50];
	TicketBooking booking_history[MAX_member];
	int num_bookings;
}Member;

// Function declarations
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
int memberMenu();
