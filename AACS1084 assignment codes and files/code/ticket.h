#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)

typedef struct {
    int hour;
    int minute;
} Time;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char nameOfCustomer[51];
    int phoneNumber;
    char memberID[16];
} CustomerDetails;

typedef struct {
    char departureLocation[51];
    char arrivalLocation[51];
} TrainLocations;

typedef struct {
    Time departureTime;
    Time arrivalTime;
} TrainTime;

typedef struct {
    Date departureDate;
    Date arrivalDate;
} TrainDate;

typedef struct {
    int seatDetails[5];
}SeatDetails;

typedef struct {
    CustomerDetails custDetails;
    char trainID[51];
    TrainLocations bookingLocation;
    TrainTime bookingTime;
    TrainDate bookingDate;
    int seatNumber;
    char paymentMethod[50];
} BookingDetails;


typedef struct {
    char trainID[11];
    TrainLocations trainLocations;
    TrainTime trainTime;
    TrainDate trainDate;
    int numberOfSeats;
    SeatDetails seatDetails;
}TrainDetails;

void modify(TrainDetails trains[], BookingDetails details[], int amountOfMembers, int availableSeats, int amountOfTrains);
void display(BookingDetails details[], int amountOfMembers);
void search(TrainDetails trains[], int amountOfTrains, int availableSeats);
void add(TrainDetails trains[], int amountOfTrains, BookingDetails details[], int amountOfMembers, int availableSeats);
void report();
void rating(BookingDetails details[], int amountOfMembers);
int ticketMenu();