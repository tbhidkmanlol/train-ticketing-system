#include "ticket.h"

int ticketMenu() {

    void modify(TrainDetails trains[], BookingDetails details[], int amountOfMembers, int availableSeats, int amountOfTrains);
    void display(BookingDetails details[], int amountOfMembers);
    void search(TrainDetails trains[], int amountOfTrains, int availableSeats);
    void add(TrainDetails trains[], int amountOfTrains, BookingDetails details[], int amountOfMembers, int availableSeats);
    void report();
    void rating(BookingDetails details[], int amountOfMembers);
    TrainDetails trains[1000];
    BookingDetails details[1000];
    int amountOfTrains = 0, amountOfMembers = 0, availableSeats = 0;
    int option = 0;

    FILE* file;
    file = fopen("dummyTrain.txt", "r");
    if (file == NULL) {
        printf("Error opening dummyTrain.txt file!\n");
        return 1;
    }


    // Scan train details from file


    // Scan train details from file
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%d:%d|%d:%d|%d/%d/%d|%d/%d/%d|%d|%d|%d|%d|%d\n",
        trains[amountOfTrains].trainID,
        trains[amountOfTrains].trainLocations.departureLocation, trains[amountOfTrains].trainLocations.arrivalLocation,
        &trains[amountOfTrains].trainTime.departureTime.hour, &trains[amountOfTrains].trainTime.departureTime.minute,
        &trains[amountOfTrains].trainTime.arrivalTime.hour, &trains[amountOfTrains].trainTime.arrivalTime.minute,
        &trains[amountOfTrains].trainDate.departureDate.day, &trains[amountOfTrains].trainDate.departureDate.month, &trains[amountOfTrains].trainDate.departureDate.year,
        &trains[amountOfTrains].trainDate.arrivalDate.day, &trains[amountOfTrains].trainDate.arrivalDate.month, &trains[amountOfTrains].trainDate.arrivalDate.year,
        &trains[amountOfTrains].seatDetails.seatDetails[0], &trains[amountOfTrains].seatDetails.seatDetails[1], &trains[amountOfTrains].seatDetails.seatDetails[2],
        &trains[amountOfTrains].seatDetails.seatDetails[3], &trains[amountOfTrains].seatDetails.seatDetails[4]) != EOF) {

        // Reset availableSeats for this train
        availableSeats = 0;

        // Calculate the number of available seats for this train
        for (int i = 0; i < 5; i++) {
            if (trains[amountOfTrains].seatDetails.seatDetails[i] != -1) {
                availableSeats++;
            }
        }
        amountOfTrains++;
    }


    fclose(file);

    FILE* fptr;
    fptr = fopen("dummyCustomer.txt", "r");
    if (fptr == NULL) {
        printf("Unable to open the file!");
        return 1;
    }

    // Scan booking details from file
    while (fscanf(fptr, "%[^|]|%d|%[^\n]\n",
        details[amountOfMembers].custDetails.nameOfCustomer, &details[amountOfMembers].custDetails.phoneNumber, details[amountOfMembers].custDetails.memberID) != EOF) {
        amountOfMembers++;
    }



    while (1) {
        printf("Welcome To Artrium's Train Sdn. Bhd Menu\n\n");
        printf("What would you like to do?\n\n");
        printf("1. Buy a Train Ticket\n");
        printf("2. Search for Trains\n");
        printf("3. Modify Customer Details\n");
        printf("4. Display Receipt\n");
        printf("5. Generate Report\n");
        printf("6. Rate Our Services\n");
        printf("7. Exit\n\n> ");
        rewind(stdin);
        scanf("%d", &option);


        switch (option) {
        case 1:
            system("cls");
            add(trains, amountOfTrains, details, amountOfMembers, availableSeats);
            break;
        case 2:
            system("cls");
            search(trains, amountOfTrains, availableSeats);
            system("pause");
            system("cls");
            break;
        case 3:
            system("cls");
            modify(trains, amountOfTrains, availableSeats, details, amountOfMembers);
            break;
        case 4:
            system("cls");
            display(details, amountOfMembers);
            break;
        case 5:
            system("cls");
            report();
            break;
        case 6:
            system("cls");
            rating(details, amountOfMembers);
            break;
        case 7:
            printf("Exiting program. Goodbye!\n");
            return 0; // Exit the program
        default:
            printf("Invalid choice. Please enter a number between 1 and 7.\n\n");
            system("pause");
            system("cls");
            break;
        }
    }

    return 0;
}
void add(TrainDetails trains[], int amountOfTrains, BookingDetails details[], int amountOfMembers, int availableSeats) {
    int trainChoice, memberChoice = -1;
    int seatNum;
    char memberID[10];
    int found;
    char paymentMethod[20], password[51];
    int paymentChoice = 0, numberOnCard, monthOfExpiry, yearOfExpiry, cvv;

    system("cls");

    // Login Part
    printf("Please Enter Your Member ID:\n> ");
    scanf("%s", memberID);
    printf("\n");

    printf("Please Enter Your Password:\n> ");
    scanf("%s", password);
    printf("\n");



    // Search for member ID in the provided customer details
    for (int i = 0; i < amountOfMembers; i++) {
        if ((strcmp(memberID, "ABC123") == 0 && strcmp(password, "lionel1") == 0 &&
            strcmp(details[i].custDetails.memberID, "ABC123") == 0) ||
            (strcmp(memberID, "ABC456") == 0 && strcmp(password, "badrul1") == 0 &&
                strcmp(details[i].custDetails.memberID, "ABC456") == 0) ||
            (strcmp(memberID, "ABC798") == 0 && strcmp(password, "jon1") == 0 &&
                strcmp(details[i].custDetails.memberID, "ABC789") == 0)) {
            memberChoice = i; // Save the index of the matching customer
            break;
        }
    }

    if (memberChoice == -1) {
        printf("Error: Member ID not found\n");
        system("pase");
        system("cls");
        return;
    }
    else {
        // Member ID found, you can use details[memberChoice] to access the customer details
        printf("Welcome, %s!\n\n", details[memberChoice].custDetails.nameOfCustomer);
        system("pause");
        system("cls");
    }

    search(trains, amountOfTrains, availableSeats);

    // Select train
    while (1) {
        printf("Please select the Train number you would like to ride: ");
        scanf("%d", &trainChoice);
        if (trainChoice >= 0 && trainChoice < amountOfTrains) {
            break; // Break the loop if a valid input is provided
        }
        else {
            printf("Invalid train choice.\n");
            system("pause");
            system("cls");
        }
    }

    // Get the seat number user wants to book
    while (1) {
        printf("Please enter the Seat Number you would like to book : ");
        scanf("%d", &seatNum);
        // Modify seat availability
        if (seatNum >= 1 && seatNum <= 5 && trains[trainChoice].seatDetails.seatDetails[seatNum - 1] != -1) {
            trains[trainChoice].seatDetails.seatDetails[seatNum - 1] = -1; // Assuming -1 indicates the seat is booked
            found = 1;
        }
        else {
            printf("Invalid seat number or seat is already booked.\n");
            found = 0;
        }

        if (found) {
            // Update display of available seats
            for (int i = 0; i < availableSeats; i++) {
                if (trains[trainChoice].seatDetails.seatDetails[i] != -1) {
                }
            }
            printf("\n");
            break; // Exit the loop if seat number is found
        }
        else {
            system("pause");
            system("cls");
        }
    }

    // Select payment method
    while (1) {
        printf("\nPlease enter Your Payment Method:\n");
        printf("1. Debit Card\n");
        printf("2. Credit Card\n");
        printf("> ");
        scanf("%d", &paymentChoice);

        if (paymentChoice == 1 || paymentChoice == 2) {
            printf("\nPlease Enter Your Number On Card (16 digits): ");
            rewind(stdin);
            if (scanf("%16lld", &numberOnCard) != 1) {
                printf("Invalid input for card number.\n");
                return; // Exit function due to invalid input
            }

            printf("\nPlease Enter Month of Card Expiry (1-12): ");
            rewind(stdin);
            if (scanf("%d", &monthOfExpiry) != 1 || monthOfExpiry < 1 || monthOfExpiry > 12) {
                printf("Invalid input for month of card expiry.\n");
                return; // Exit function due to invalid input
            }

            printf("\nPlease Enter Year Of Card Expiry: ");
            rewind(stdin);
            if (scanf("%d", &yearOfExpiry) < !23) {
                printf("The Card Has Already Expiried.\n");
                return; // Exit function due to invalid input
            }

            printf("\nPlease Enter Card CVV (3 digits): ");
            rewind(stdin);
            if (scanf("%3d", &cvv) != 1) {
                printf("Invalid input for card CVV.\n");
                return; // Exit function due to invalid input
            }

            FILE* fptr = fopen("cardDetails.txt", "a");
            if (fptr == NULL) {
                printf("Unable to open file.\n");
                return;
            }

            fprintf(fptr, "%s|%d|%s|%d|%d|%d|%d\n",
                details[memberChoice].custDetails.nameOfCustomer,
                details[memberChoice].custDetails.phoneNumber,
                details[memberChoice].custDetails.memberID,
                numberOnCard, monthOfExpiry, yearOfExpiry, cvv);

            fclose(fptr);
            break; // Break the loop after successful payment input

        }
        else {
            printf("Invalid payment method. Please enter Debit Card, Credit Card, or Pay Cash On Location\n");
            system("pause");
            system("cls");
        }
    }

    if (paymentChoice == 1) {
        strcpy(paymentMethod, "Debit Card");
    }
    else {
        strcpy(paymentMethod, "Credit Card");

    }


    // Confirm the booking
    char confirm;
    printf("\nConfirm booking (Y/N): ");
    rewind(stdin);
    scanf("%c", &confirm);

    if (confirm != 'Y' && confirm != 'y') {
        printf("Booking canceled.\n");
        system("pause");
        system("cls");
        return;
    }

    FILE* file = fopen("trainDetails.txt", "a");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    // Write common details
    fprintf(file, "%s|%s|%s|%02d:%02d|%02d:%02d|%d/%d/%d|%d/%d/%d\n",
        trains[trainChoice].trainID,
        trains[trainChoice].trainLocations.departureLocation, trains[trainChoice].trainLocations.arrivalLocation,
        trains[trainChoice].trainTime.departureTime.hour, trains[trainChoice].trainTime.departureTime.minute,
        trains[trainChoice].trainTime.arrivalTime.hour, trains[trainChoice].trainTime.arrivalTime.minute,
        trains[trainChoice].trainDate.departureDate.day, trains[trainChoice].trainDate.departureDate.month, trains[trainChoice].trainDate.departureDate.year,
        trains[trainChoice].trainDate.arrivalDate.day, trains[trainChoice].trainDate.arrivalDate.month, trains[trainChoice].trainDate.arrivalDate.year);

    // Iterate over all available seats
    for (int i = 0; i < availableSeats; i++) {
        if (trains[trainChoice].seatDetails.seatDetails[i] != -1) {
            // Seat is available, so print its number
            fprintf(file, "%d|", i + 1);
        }
    }

    fprintf(file, "\n");
    fclose(file);


    FILE* file1 = fopen("customerBooking.txt", "a");
    if (file1 == NULL) {
        printf("Unable to open file!\n");
        return;
    }

    // Write booking details to the file
    fprintf(file1, "%s|%d|%s|%s|%s|%s|%02d:%02d|%02d:%02d|%d/%d/%d|%d/%d/%d|%d|%s\n",
        details[memberChoice].custDetails.nameOfCustomer,
        details[memberChoice].custDetails.phoneNumber,
        details[memberChoice].custDetails.memberID,
        trains[trainChoice].trainID,
        trains[trainChoice].trainLocations.departureLocation, trains[trainChoice].trainLocations.arrivalLocation,
        trains[trainChoice].trainTime.departureTime.hour, trains[trainChoice].trainTime.departureTime.minute,
        trains[trainChoice].trainTime.arrivalTime.hour, trains[trainChoice].trainTime.arrivalTime.minute,
        trains[trainChoice].trainDate.departureDate.day, trains[trainChoice].trainDate.departureDate.month, trains[trainChoice].trainDate.departureDate.year,
        trains[trainChoice].trainDate.arrivalDate.day, trains[trainChoice].trainDate.arrivalDate.month, trains[trainChoice].trainDate.arrivalDate.year,
        seatNum, paymentMethod);
    fclose(file1);

    printf("Booking successful!\n");
    system("pause");
    system("cls");
    main();
}
void search(TrainDetails trains[], int amountOfTrains, int availableSeats) {
    int choice;

    printf("Please Choose which Train You Would like to Search: \n");
    printf("1. T150\n");
    printf("2. T250\n");
    printf("3. Display All Trains\n\n> ");
    scanf("%d", &choice);

    system("cls");

    switch (choice) {
    case 1:
    case 2:
        for (int i = 0; i < amountOfTrains; i++) {
            if ((choice == 1 && strcmp(trains[i].trainID, "T150") == 0) ||
                (choice == 2 && strcmp(trains[i].trainID, "T250") == 0)) {
                printf("Train Number: %d\n", i);
                printf("Train ID: %s\n", trains[i].trainID);
                printf("Departure Location: %s\n", trains[i].trainLocations.departureLocation);
                printf("Arrival Location: %s\n", trains[i].trainLocations.arrivalLocation);
                printf("Departure Time: %02d:%02d\n", trains[i].trainTime.departureTime.hour, trains[i].trainTime.departureTime.minute);
                printf("Arrival Time: %02d:%02d\n", trains[i].trainTime.arrivalTime.hour, trains[i].trainTime.arrivalTime.minute);
                printf("Departure Date: %d/%d/%d\n", trains[i].trainDate.departureDate.day,
                    trains[i].trainDate.departureDate.month, trains[i].trainDate.departureDate.year);
                printf("Arrival Date: %d/%d/%d\n", trains[i].trainDate.arrivalDate.day,
                    trains[i].trainDate.arrivalDate.month, trains[i].trainDate.arrivalDate.year);
                printf("Available Seat Number(s): ");
                for (int j = 0; j < availableSeats; j++) {
                    if (trains[i].seatDetails.seatDetails[j] != -1) {
                        printf("%d ", j + 1);
                    }
                }
                printf("\n\n");
            }
        }
        break;

    case 3:
        // Display all trains
        for (int i = 0; i < amountOfTrains; i++) {
            printf("Train Number: %d\n", i);
            printf("Train ID: %s\n", trains[i].trainID);
            printf("Departure Location: %s\n", trains[i].trainLocations.departureLocation);
            printf("Arrival Location: %s\n", trains[i].trainLocations.arrivalLocation);
            printf("Departure Time: %02d:%02d\n", trains[i].trainTime.departureTime.hour, trains[i].trainTime.departureTime.minute);
            printf("Arrival Time: %02d:%02d\n", trains[i].trainTime.arrivalTime.hour, trains[i].trainTime.arrivalTime.minute);
            printf("Departure Date: %d/%d/%d\n", trains[i].trainDate.departureDate.day,
                trains[i].trainDate.departureDate.month, trains[i].trainDate.departureDate.year);
            printf("Arrival Date: %d/%d/%d\n", trains[i].trainDate.arrivalDate.day,
                trains[i].trainDate.arrivalDate.month, trains[i].trainDate.arrivalDate.year);
            printf("Available Seat Number(s): ");
            for (int j = 0; j < availableSeats; j++) {
                if (trains[i].seatDetails.seatDetails[j] != -1) {
                    printf("%d ", j + 1);
                }
            }
            printf("\n\n");
        }
        break;

    default:
        printf("Invalid choice.\n");
        break;
    }

}



void modify(TrainDetails trains[], int amountOfMembers, int availableSeats, int amountOfTrains) {
    char password[51], memberID[10], custChoice = 0;
    int modification = 0, indexToUpdate = -1;

    FILE* file = fopen("customerBooking.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    BookingDetails details[5];

    // Read data from the file
    for (int i = 0; i < 5; i++) {
        fscanf(file, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%02d:%02d|%02d:%02d|%d/%d/%d|%d/%d/%d|%d|%[^\n]\n",
            details[i].custDetails.nameOfCustomer,
            &details[i].custDetails.phoneNumber,
            details[i].custDetails.memberID,
            details[i].trainID,
            details[i].bookingLocation.departureLocation,
            details[i].bookingLocation.arrivalLocation,
            &details[i].bookingTime.departureTime.hour, &details[i].bookingTime.departureTime.minute,
            &details[i].bookingTime.arrivalTime.hour, &details[i].bookingTime.arrivalTime.minute,
            &details[i].bookingDate.departureDate.day, &details[i].bookingDate.departureDate.month, &details[i].bookingDate.departureDate.year,
            &details[i].bookingDate.arrivalDate.day, &details[i].bookingDate.arrivalDate.month, &details[i].bookingDate.arrivalDate.year,
            &details[i].seatNumber,
            details[i].paymentMethod);
    }

    fclose(file);

    printf("Please enter your Member ID: ");
    scanf("%s", memberID);

    printf("Please enter your password: ");
    scanf("%s", password);

    do {
        // Reset indexToUpdate
        indexToUpdate = -1;

        // Find the matching record
        for (int i = 0; i < 5; i++) {
            if ((strcmp(memberID, "ABC123") == 0 && strcmp(password, "lionel1") == 0 &&
                strcmp(details[i].custDetails.memberID, "ABC123") == 0) ||
                (strcmp(memberID, "ABC456") == 0 && strcmp(password, "badrul1") == 0 &&
                    strcmp(details[i].custDetails.memberID, "ABC456") == 0) ||
                (strcmp(memberID, "ABC798") == 0 && strcmp(password, "jon1") == 0 &&
                    strcmp(details[i].custDetails.memberID, "ABC798") == 0)) {

                // Store the index of the matching record
                indexToUpdate = i;
                break; // Exit the loop once a match is found
            }
        }

        if (indexToUpdate != -1) { // Display details only if a match is found
            // Display the welcome message
            printf("Welcome %s!\n\n", details[indexToUpdate].custDetails.nameOfCustomer);
            system("pause");
            system("cls");

            printf("Name: %s\n", details[indexToUpdate].custDetails.nameOfCustomer);
            printf("Phone Number: 0%d\n", details[indexToUpdate].custDetails.phoneNumber);
            printf("Member ID: %s\n", details[indexToUpdate].custDetails.memberID);
            printf("\nTicket Details:");
            printf("\nTrain ID: %s\n", details[indexToUpdate].trainID);
            printf("Departure Location: %s\n", details[indexToUpdate].bookingLocation.departureLocation);
            printf("Arrival Location: %s\n", details[indexToUpdate].bookingLocation.arrivalLocation);
            printf("Departure Time: %02d:%02d\n", details[indexToUpdate].bookingTime.departureTime.hour, details[indexToUpdate].bookingTime.departureTime.minute);
            printf("Arrival Time: %02d:%02d\n", details[indexToUpdate].bookingTime.arrivalTime.hour, details[indexToUpdate].bookingTime.arrivalTime.minute);
            printf("Departure Date: %d/%d/%d\n", details[indexToUpdate].bookingDate.departureDate.day, details[indexToUpdate].bookingDate.departureDate.month, details[indexToUpdate].bookingDate.departureDate.year);
            printf("Arrival Date: %d/%d/%d\n", details[indexToUpdate].bookingDate.arrivalDate.day, details[indexToUpdate].bookingDate.arrivalDate.month, details[indexToUpdate].bookingDate.arrivalDate.year);
            printf("Seat Number: %d\n", details[indexToUpdate].seatNumber);
            printf("Payment Method: %s\n", details[indexToUpdate].paymentMethod);
        }
        else {
            printf("Invalid Member ID or Password!\n");
        }

        printf("\n\n");

        printf("Please choose which data you would like to change: \n");
        printf("1. Train ID\n");
        printf("2. Seat ID\n> ");
        scanf("%d", &modification);

        printf("\n\n");
        system("pause");
        system("cls");

        switch (modification) {
        case 1:
            printf("Enter the new Train ID you would like to ride (available T150 & T250): ");
            scanf("%s", details[indexToUpdate].trainID);
            break;

        case 2:
            printf("Enter the new Seat Number (1,2,3,4,5): ");
            scanf("%d", &details[indexToUpdate].seatNumber); // Use %d for integer
            break;

        default:
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
        }

        printf("\nModification successful!\n\n");
        printf("Do you want to modify more? (Y/N): ");
        scanf(" %c", &custChoice);

        printf("\n\n");
        system("pause");
        system("cls");

    } while (toupper(custChoice) == 'Y');

    // Convert payment method integer to string
    for (int i = 0; i < 5; i++) {
        if (details[i].paymentMethod == 1) {
            strcpy(details[i].paymentMethod, "Cash");
        }
        else if (details[i].paymentMethod == 2) {
            strcpy(details[i].paymentMethod, "Credit Card");
        }
        else {
            strcpy(details[i].paymentMethod, "Debit Card");
        }
    }

    // Open the file in write mode to overwrite the data
    file = fopen("customerBooking.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < 5; i++) {
        fprintf(file, "%s|%d|%s|%s|%s|%s|%02d:%02d|%02d:%02d|%d/%d/%d|%d/%d/%d|%d|%s\n",
            details[i].custDetails.nameOfCustomer,
            details[i].custDetails.phoneNumber,
            details[i].custDetails.memberID,
            details[i].trainID,
            details[i].bookingLocation.departureLocation,
            details[i].bookingLocation.arrivalLocation,
            details[i].bookingTime.departureTime.hour, details[i].bookingTime.departureTime.minute,
            details[i].bookingTime.arrivalTime.hour, details[i].bookingTime.arrivalTime.minute,
            details[i].bookingDate.departureDate.day, details[i].bookingDate.departureDate.month, details[i].bookingDate.departureDate.year,
            details[i].bookingDate.arrivalDate.day, details[i].bookingDate.arrivalDate.month, details[i].bookingDate.arrivalDate.year,
            details[i].seatNumber,
            details[i].paymentMethod);
    }

    fclose(file);

    system("cls");
}




void display(BookingDetails details[], int amountOfMembers) {
    char password[51], memberID[10];
    int indexToUpdate = -1;

    FILE* file = fopen("customerBooking.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Read data from the file
    for (int i = 0; i < amountOfMembers; i++) {
        fscanf(file, "%[^|]|%d|%[^|]|%[^|]|%[^|]|%[^|]|%02d:%02d|%02d:%02d|%d/%d/%d|%d/%d/%d|%d|%[^\n]\n",
            details[i].custDetails.nameOfCustomer,
            &details[i].custDetails.phoneNumber,
            details[i].custDetails.memberID,
            details[i].trainID,
            details[i].bookingLocation.departureLocation,
            details[i].bookingLocation.arrivalLocation,
            &details[i].bookingTime.departureTime.hour, &details[i].bookingTime.departureTime.minute,
            &details[i].bookingTime.arrivalTime.hour, &details[i].bookingTime.arrivalTime.minute,
            &details[i].bookingDate.departureDate.day, &details[i].bookingDate.departureDate.month, &details[i].bookingDate.departureDate.year,
            &details[i].bookingDate.arrivalDate.day, &details[i].bookingDate.arrivalDate.month, &details[i].bookingDate.arrivalDate.year,
            &details[i].seatNumber, // Changed to &details[i].seatNumber
            details[i].paymentMethod);
    }

    fclose(file);

    printf("Please enter your Member ID: ");
    scanf("%s", memberID);

    printf("Please enter your password: ");
    scanf("%s", password);

    // Find the matching record
    for (int i = 0; i < amountOfMembers; i++) {
        if ((strcmp(memberID, "ABC123") == 0 && strcmp(password, "lionel1") == 0 &&
            strcmp(details[i].custDetails.memberID, "ABC123") == 0) ||
            (strcmp(memberID, "ABC456") == 0 && strcmp(password, "badrul1") == 0 &&
                strcmp(details[i].custDetails.memberID, "ABC456") == 0) ||
            (strcmp(memberID, "ABC798") == 0 && strcmp(password, "jon1") == 0 &&
                strcmp(details[i].custDetails.memberID, "ABC789") == 0)) {

            // Store the index of the matching record
            indexToUpdate = i;
            break; // Exit the loop once a match is found
        }
    }

    if (indexToUpdate != -1) {
        // Display the welcome message
        printf("Welcome %s!\n\n", details[indexToUpdate].custDetails.nameOfCustomer);
        system("pause");
        system("cls");

        // Display the booking details
        printf("Name: %s\n", details[indexToUpdate].custDetails.nameOfCustomer);
        printf("Phone Number: 0%d\n", details[indexToUpdate].custDetails.phoneNumber);
        printf("Member ID: %s\n", details[indexToUpdate].custDetails.memberID);
        printf("\nTicket Details:");
        printf("\nTrain ID: %s\n", details[indexToUpdate].trainID);
        printf("Departure Location: %s\n", details[indexToUpdate].bookingLocation.departureLocation);
        printf("Arrival Location: %s\n", details[indexToUpdate].bookingLocation.arrivalLocation);
        printf("Departure Time: %02d:%02d\n", details[indexToUpdate].bookingTime.departureTime.hour, details[indexToUpdate].bookingTime.departureTime.minute);
        printf("Arrival Time: %02d:%02d\n", details[indexToUpdate].bookingTime.arrivalTime.hour, details[indexToUpdate].bookingTime.arrivalTime.minute);
        printf("Departure Date: %d/%d/%d\n", details[indexToUpdate].bookingDate.departureDate.day, details[indexToUpdate].bookingDate.departureDate.month, details[indexToUpdate].bookingDate.departureDate.year);
        printf("Arrival Date: %d/%d/%d\n", details[indexToUpdate].bookingDate.arrivalDate.day, details[indexToUpdate].bookingDate.arrivalDate.month, details[indexToUpdate].bookingDate.arrivalDate.year);
        printf("Seat Number: %d\n", details[indexToUpdate].seatNumber);
        printf("Payment Method: %s\n", details[indexToUpdate].paymentMethod);
    }
    else {
        printf("Invalid Member ID or Password!\n");
        return;
    }
    printf("\n\n");
    system("pause");
    system("cls");
}


void report() {
    int option, option2, option3, weeklySales = 0, monthlySales = 0, numberOfMonth = 0, numberOfDays = 0;
    int monTicket, tueTicket, wedTicket, thuTicket, friTicket, satTicket, sunTicket;
    float weeklyRevenue = 0, monthlyRevenue = 0;
    int weekTicket1, weekTicket2, weekTicket3, weekTicket4;

    printf("Please Choose what you would like to do:\n");
    printf("1. Report on Ticket Sales this Week\n");
    printf("2. Report on Targeted Revenue\n> ");
    rewind(stdin);
    scanf("%d", &option);

    if (option == 1) {
        printf("\n\nWould you Like Ticket Sales for: \n");
        printf("1. This Week\n");
        printf("2. This Month\n> ");
        rewind(stdin);
        scanf("%d", &option2);

        printf("\n\n");
        system("pause");
        system("cls");

        printf("Weekly Sales\n\n");

        if (option2 == 1) {
            printf("Enter Number Of Ticket Sales On Monday: ");
            rewind(stdin);
            scanf("%d", &monTicket);

            printf("Enter Number Of Ticket Sales On Tuesday: ");
            rewind(stdin);
            scanf("%d", &tueTicket);

            printf("Enter Number Of Ticket Sales On Wednesday: ");
            rewind(stdin);
            scanf("%d", &wedTicket);

            printf("Enter Number Of Ticket Sales On Thursday: ");
            rewind(stdin);
            scanf("%d", &thuTicket);

            printf("Enter Number Of Ticket Sales On Friday: ");
            rewind(stdin);
            scanf("%d", &friTicket);

            printf("Enter Number Of Ticket Sales On Saturday: ");
            rewind(stdin);
            scanf("%d", &satTicket);

            printf("Enter Number Of Ticket Sales On Sunday: ");
            rewind(stdin);
            scanf("%d", &sunTicket);

            printf("\n\n");
            system("pause");
            system("cls");

            printf("Monday   : ");
            for (int a = 0; a < monTicket; a++) {
                printf("*");
            }
            printf("\n");

            printf("Tuesday  : ");
            for (int b = 0; b < tueTicket; b++) {
                printf("*");
            }
            printf("\n");

            printf("Wednesday: ");
            for (int c = 0; c < wedTicket; c++) {
                printf("*");
            }
            printf("\n");

            printf("Thursday : ");
            for (int d = 0; d < thuTicket; d++) {
                printf("*");
            }
            printf("\n");

            printf("Friday   : ");
            for (int e = 0; e < friTicket; e++) {
                printf("*");
            }
            printf("\n");

            printf("Saturday : ");
            for (int f = 0; f < satTicket; f++) {
                printf("*");
            }
            printf("\n");

            printf("Sunday   : ");
            for (int g = 0; g < sunTicket; g++) {
                printf("*");
            }
            printf("\n");
            system("pause");
            system("cls");


        }
        else if (option2 == 2) {
            printf("Enter Number Of Ticket Sales On The 1st Week: ");
            rewind(stdin);
            scanf("%d", &weekTicket1);

            printf("Enter Number Of Ticket Sales On The 2nd Week: ");
            rewind(stdin);
            scanf("%d", &weekTicket2);

            printf("Enter Number Of Ticket Sales On The 3rd Week: ");
            rewind(stdin);
            scanf("%d", &weekTicket3);

            printf("Enter Number Of Ticket Sales On The 4th Week: ");
            rewind(stdin);
            scanf("%d", &weekTicket4);

            weekTicket1 = weekTicket1 / 20;
            weekTicket2 = weekTicket2 / 20;
            weekTicket3 = weekTicket3 / 20;
            weekTicket4 = weekTicket4 / 20;


            printf("Each * Represemts 20 Tickets\n\n");

            printf("1st Week: ");
            for (int week1 = 0; week1 < weekTicket1; week1++) {
                printf("*");
            }
            printf("\n");

            printf("2nd Week: ");
            for (int week2 = 0; week2 < weekTicket2; week2++) {
                printf("*");
            }
            printf("\n");

            printf("3rd Week: ");
            for (int week3 = 0; week3 < weekTicket3; week3++) {
                printf("*");
            }
            printf("\n");

            printf("4th Week: ");
            for (int week4 = 0; week4 < weekTicket4; week4++) {
                printf("*");
            }
            printf("\n");

        }
    }

    else if (option == 2) {
        printf("\n\nWould You Like Targeted Revenue for: \n");
        printf("1. This Week\n");
        printf("2. This Month\n");
        rewind(stdin);
        scanf("%d", &option3);

        if (option3 == 1) {
            printf("\n\nPlease Enter Targeted Revenue for This Week: RM");
            rewind(stdin);
            scanf("%f", &weeklyRevenue);

            weeklySales = (int)ceil(weeklyRevenue / 50); // Round up to the next whole number

            printf("\nThe number of ticket sales that has to be made this week is: %d\n\n", weeklySales);
        }
        else if (option3 == 2) {
            printf("\n\nPlease Enter Targeted Revenue for This Month: RM");
            rewind(stdin);
            scanf("%f", &monthlyRevenue);

            printf("Please Enter the Number of The month: ");
            rewind(stdin);
            scanf("%d", &numberOfMonth);

            switch (numberOfMonth) {
            case 1:
                numberOfDays = 31;
                break;
            case 2:
                numberOfDays = 28;
                break;
            case 3:
                numberOfDays = 31;
                break;
            case 4:
                numberOfDays = 30;
                break;
            case 5:
                numberOfDays = 31;
                break;
            case 6:
                numberOfDays = 30;
                break;
            case 7:
                numberOfDays = 31;
                break;
            case 8:
                numberOfDays = 31;
                break;
            case 9:
                numberOfDays = 30;
                break;
            case 10:
                numberOfDays = 31;
                break;
            case 11:
                numberOfDays = 30;
                break;
            case 12:
                numberOfDays = 31;
                break;
            }

            monthlySales = (int)ceil(monthlyRevenue / numberOfDays); // Round up to the next whole number

            printf("\n\nThe number of ticket sales that has to be made this month is: %d\n", monthlySales);
        }
    }
}

void rating(BookingDetails details[], int amountOfMembers) {
    char comment[250], memberID[6]; // Maximum comment size including null terminator
    int option, memberChoice;

    printf("Please Enter Your Member ID:\n> ");
    scanf("%s", memberID);
    printf("\n\n");

    // Search for member ID in the provided customer details
    memberChoice = -1;
    for (int i = 0; i < amountOfMembers; i++) {
        if (strcmp(details[i].custDetails.memberID, memberID) == 0) {
            memberChoice = i; // Save the index of the matching customer
            break;
        }
    }

    if (memberChoice == -1) {
        printf("Error: Member ID not found\n");
        return;
    }

    printf("Please Choose Our Customer Service To Rate:\n");
    printf("1. Program Service\n");
    printf("2. Train Service\n");
    printf("3. Any Opinion On our Service\n> ");
    scanf("%d", &option);

    system("pause");
    system("cls");

    if (option == 1) {
        int answer1, answer2, answer3, answer4, answer5;

        printf("On a Scale of 1 to 10:\n");
        printf("Please Rate our Program Services on a Scale of 1 to 5 where\n");
        printf("1. Strongly Agree\n");
        printf("2. Agree\n");
        printf("3. Neutral\n");
        printf("4. Disagree\n");
        printf("5. Strongly Disagree\n\n");

        printf("To what extent do you strongly agree that our train ticket booking interface is user-friendly?\n> ");
        scanf("%d", &answer1);

        printf("\nHow much do you strongly agree that the variety of payment options available for booking tickets meets your needs?\n> ");
        scanf("%d", &answer2);

        printf("\nHow strongly do you agree that it is convenient to modify or cancel booked tickets through our program?\n> ");
        scanf("%d", &answer3);

        printf("\nTo what extent do you strongly agree that our program provides clear and readily available seat selection information?\n> ");
        scanf("%d", &answer4);

        printf("\nTo what extent do you strongly agree that our system provides timely and accurate updates on train schedules?\n> ");
        scanf("%d", &answer5);

        FILE* file1 = fopen("customerRatings.txt", "a");
        if (file1 == NULL) {
            printf("Error opening File!");
            exit(-1);
        }

        fprintf(file1, "Answers 1 - 5: %d|%d|%d|%d|%d\n", answer1, answer2, answer3, answer4, answer5);
        fclose(file1);

        printf("Thank You For Rating\n\n");

        system("pause");
        return;
    }
    else if (option == 2) {
        int answer6, answer7, answer8, answer9, answer10;

        printf("Please Rate our Train Services on a Scale of 1 to 5 where\n");
        printf("1. Strongly Agree\n");
        printf("2. Agree\n");
        printf("3. Neutral\n");
        printf("4. Disagree\n");
        printf("5. Strongly Disagree\n\n");

        printf("To what extent do you strongly agree that our train services are reliable and punctual?\n> ");
        scanf("%d", &answer6);

        printf("\nHow much do you strongly agree that the cleanliness and hygiene of our trains are maintained?\n> ");
        scanf("%d", &answer7);

        printf("\nHow strongly do you agree that the onboard facilities and amenities meet your expectations?\n> ");
        scanf("%d", &answer8);

        printf("\nTo what extent do you strongly agree that our customer service for train-related inquiries and assistance is satisfactory?\n> ");
        scanf("%d", &answer9);

        printf("\nTo what extent do you strongly agree that our train routes and schedules are well-organized and easy to understand?\n> ");
        scanf("%d", &answer10);

        FILE* file1 = fopen("customerRatings.txt", "a");
        if (file1 == NULL) {
            printf("Error opening File!");
            exit(-1);
        }

        fprintf(file1, "Answers 6 - 10: %d|%d|%d|%d|%d\n", answer6, answer7, answer8, answer9, answer10);

        fclose(file1);

        printf("Thank You For Rating\n\n");
        system("pause");
        return;

    }
    else if (option == 3) {
        printf("Please Enter how we could improve our Services.\n> ");
        getchar(); // Consume the newline character left in the buffer
        fgets(comment, sizeof(comment), stdin); // Read the comment
        comment[strcspn(comment, "\n")] = '\0'; // Remove trailing newline

        FILE* file = fopen("customerComments.txt", "a");
        if (file == NULL) {
            printf("Error opening file.\n");
            exit(1);
        }
        fprintf(file, "%s|%d|%s|%s\n",
            details[memberChoice].custDetails.nameOfCustomer,
            details[memberChoice].custDetails.phoneNumber,
            details[memberChoice].custDetails.memberID, comment);
        fclose(file);
        printf("Comment saved successfully.\n");
        system("pause");
    }
    else {
        printf("Invalid option.\n");
        return;
    }
}


