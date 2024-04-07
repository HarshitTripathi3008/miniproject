#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINS 5
#define MAX_SEATS_PER_TRAIN 50
#define MAX_PNR_LENGTH 10

#define FARE_SLEEPER 500
#define FARE_FIRST_AC 2000
#define FARE_SECOND_AC 1500
#define FARE_THIRD_AC 1000
#define FARE_GENERAL 200

typedef struct {
    int seatNumber;
    char passengerName[50];
    int isReserved;
    int isPaid;
    char pnr[MAX_PNR_LENGTH];
    double fare;
} Seat;

typedef struct {
    int trainNumber;
    char trainName[50];
    Seat seats[MAX_SEATS_PER_TRAIN];
} Train;

Train trains[MAX_TRAINS];

void initializeTrains() {
    int trainNumbers[] = {1, 2, 3, 4, 5};
    char trainNames[][50] = {
        "Rajdhani Express",
        "Shatabdi Express",
        "Duronto Express",
        "Humsafar Express",
        "Garib Rath Express"
    };

    for (int i = 0; i < MAX_TRAINS; i++) {
        trains[i].trainNumber = trainNumbers[i];
        strcpy(trains[i].trainName, trainNames[i]);

        for (int j = 0; j < MAX_SEATS_PER_TRAIN; j++) {
            trains[i].seats[j].seatNumber = j + 1;
            trains[i].seats[j].isReserved = 0;
            trains[i].seats[j].isPaid = 0;
            strcpy(trains[i].seats[j].passengerName, "");
            strcpy(trains[i].seats[j].pnr, "");

            if (j < 10) {
                trains[i].seats[j].fare = FARE_FIRST_AC;
            } else if (j < 20) {
                trains[i].seats[j].fare = FARE_SECOND_AC;
            } else if (j < 30) {
                trains[i].seats[j].fare = FARE_THIRD_AC;
            } else if (j < 40) {
                trains[i].seats[j].fare = FARE_SLEEPER;
            } else {
                trains[i].seats[j].fare = FARE_GENERAL;
            }
        }
    }
}

void generatePNR(char* pnr) {
    for (int i = 0; i < MAX_PNR_LENGTH - 1; i++) {
        pnr[i] = '0' + rand() % 10;
    }
    pnr[MAX_PNR_LENGTH - 1] = '\0';
}

void displayAvailableTrains() {
    printf("\nAvailable Trains:\n");
    printf("Train No\tTrain Name\n");

    for (int i = 0; i < MAX_TRAINS; i++) {
        printf("%d\t\t%s\n", trains[i].trainNumber, trains[i].trainName);
    }
}

void displayAvailableSeats(int trainNumber) {
    if (trainNumber < 1 || trainNumber > MAX_TRAINS) {
        printf("Invalid train number. Please try again.\n");
        return;
    }

    printf("\nAvailable Seats for %s:\n", trains[trainNumber - 1].trainName);
    printf("Seat No\tClass\tStatus\tFare\n");

    for (int i = 0; i < MAX_SEATS_PER_TRAIN; i++) {
        const char* seatClass;

        if (i < 10) {
            seatClass = "First AC";
        } else if (i < 20) {
            seatClass = "Second AC";
        } else if (i < 30) {
            seatClass = "Third AC";
        } else if (i < 40) {
            seatClass = "Sleeper";
        } else {
            seatClass = "General";
        }

        if (!trains[trainNumber - 1].seats[i].isReserved) {
            printf("%d\t%s\tAvailable\t%.2f\n", trains[trainNumber - 1].seats[i].seatNumber,
                   seatClass, trains[trainNumber - 1].seats[i].fare);
        }
    }
}

int getUserPaymentChoice() {
    int paymentChoice;

    printf("\nChoose the method of payment:\n");
    printf("1. Credit Card\n");
    printf("2. Debit Card\n");
    printf("3. Net Banking\n");

    do {
        printf("Enter your choice (1-3): ");
        if (scanf("%d", &paymentChoice) != 1 || paymentChoice < 1 || paymentChoice > 3) {
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            while (getchar() != '\n');  
        }
    } while (paymentChoice < 1 || paymentChoice > 3);

    return paymentChoice;
}

void bookTicket(int trainNumber) {
    if (trainNumber < 1 || trainNumber > MAX_TRAINS) {
        printf("Invalid train number. Please try again.\n");
        return;
    }

    int seatNo;
    printf("\nEnter the seat number to book for %s (%d):\n", trains[trainNumber - 1].trainName, trains[trainNumber - 1].trainNumber);

    if (scanf("%d", &seatNo) != 1 || seatNo < 1 || seatNo > MAX_SEATS_PER_TRAIN) {
        printf("Invalid seat number. Please try again.\n");
        while (getchar() != '\n');  
        return;
    }

    if (trains[trainNumber - 1].seats[seatNo - 1].isReserved) {
        printf("Seat already reserved. Please choose another seat.\n");
    } else {
        printf("Enter passenger name: ");
        scanf("%49s", trains[trainNumber - 1].seats[seatNo - 1].passengerName);

        generatePNR(trains[trainNumber - 1].seats[seatNo - 1].pnr);

        
        int paymentChoice = getUserPaymentChoice();

        
        int paymentSuccess = 1;
        if (paymentSuccess) {
            printf("Payment Successful!\n");
            trains[trainNumber - 1].seats[seatNo - 1].isReserved = 1;
            trains[trainNumber - 1].seats[seatNo - 1].isPaid = 1;
            printf("Ticket booked successfully! Your PNR is: %s\n", trains[trainNumber - 1].seats[seatNo - 1].pnr);
        } else {
            printf("Payment failed. Please try again.\n");
        }
    }
}

void displayReservationStatus(int trainNumber) {
    if (trainNumber < 1 || trainNumber > MAX_TRAINS) {
        printf("Invalid train number. Please try again.\n");
        return;
    }

    printf("\nReservation Status for %s:\n", trains[trainNumber - 1].trainName);
    printf("Seat No\tClass\tPassenger Name\tPNR\t\t\tPayment Status\tFare\n");

    for (int i = 0; i < MAX_SEATS_PER_TRAIN; i++) {
        const char* seatClass;

        if (i < 10) {
            seatClass = "First AC";
        } else if (i < 20) {
            seatClass = "Second AC";
        } else if (i < 30) {
            seatClass = "Third AC";
        } else if (i < 40) {
            seatClass = "Sleeper";
        } else {
            seatClass = "General";
        }

        printf("%d\t%s\t%s\t\t%s\t\t%s\t\t%.2f\n", trains[trainNumber - 1].seats[i].seatNumber,
               seatClass, trains[trainNumber - 1].seats[i].passengerName,
               trains[trainNumber - 1].seats[i].pnr,
               trains[trainNumber - 1].seats[i].isPaid ? "Paid" : "Not Paid",
               trains[trainNumber - 1].seats[i].fare);
    }
}

void showAllReservations() {
    printf("\nAll Reservations for Different Classes:\n");
    printf("Train No\tSeat No\tClass\tPassenger Name\tPNR\t\t\tPayment Status\tFare\n");

    for (int i = 0; i < MAX_TRAINS; i++) {
        for (int j = 0; j < MAX_SEATS_PER_TRAIN; j++) {
            const char* seatClass;

            if (j < 10) {
                seatClass = "First AC";
            } else if (j < 20) {
                seatClass = "Second AC";
            } else if (j < 30) {
                seatClass = "Third AC";
            } else if (j < 40) {
                seatClass = "Sleeper";
            } else {
                seatClass = "General";
            }

            if (trains[i].seats[j].isReserved) {
                printf("%d\t\t%d\t\t%s\t%s\t\t%s\t\t%s\t\t%.2f\n", trains[i].trainNumber,
                       trains[i].seats[j].seatNumber, seatClass, trains[i].seats[j].passengerName,
                       trains[i].seats[j].pnr, trains[i].seats[j].isPaid ? "Paid" : "Not Paid",
                       trains[i].seats[j].fare);
            }
        }
    }
}

void showBookedTicket(int trainNumber) {
    if (trainNumber < 1 || trainNumber > MAX_TRAINS) {
        printf("Invalid train number. Please try again.\n");
        return;
    }

    char userPNR[MAX_PNR_LENGTH];
    printf("\nEnter your PNR to view the booked ticket: ");
    scanf("%s", userPNR);

    for (int i = 0; i < MAX_SEATS_PER_TRAIN; i++) {
        if (trains[trainNumber - 1].seats[i].isReserved && strcmp(trains[trainNumber - 1].seats[i].pnr, userPNR) == 0) {
            const char* seatClass;

            if (i < 10) {
                seatClass = "First AC";
            } else if (i < 20) {
                seatClass = "Second AC";
            } else if (i < 30) {
                seatClass = "Third AC";
            } else if (i < 40) {
                seatClass = "Sleeper";
            } else {
                seatClass = "General";
            }

            printf("\nBooked Ticket Details:\n");
            printf("Train No: %d\n", trains[trainNumber - 1].trainNumber);
            printf("Train Name: %s\n", trains[trainNumber - 1].trainName);
            printf("Seat No: %d\n", trains[trainNumber - 1].seats[i].seatNumber);
            printf("Class: %s\n", seatClass);
            printf("Passenger Name: %s\n", trains[trainNumber - 1].seats[i].passengerName);
            printf("PNR: %s\n", trains[trainNumber - 1].seats[i].pnr);
            printf("Payment Status: %s\n", trains[trainNumber - 1].seats[i].isPaid ? "Paid" : "Not Paid");
            printf("Fare: %.2f\n", trains[trainNumber - 1].seats[i].fare);
            return;
        }
    }

    printf("Invalid PNR. No matching reservation found.\n");
}

int main() {
    initializeTrains();

    int choice, trainChoice;

    do {
        printf("\nRailway Reservation System\n");
        printf("1. Display Available Trains\n");
        printf("2. Display Available Seats\n");
        printf("3. Book Ticket\n");
        printf("4. Display Reservation Status\n");
        printf("5. Show All Reservations\n");
        printf("6. Show Booked Ticket\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  
            continue;  
        }

        switch (choice) {
            case 1:
                displayAvailableTrains();
                break;
            case 2:
                printf("\nEnter the train number: ");
                if (scanf("%d", &trainChoice) != 1 || trainChoice < 1 || trainChoice > MAX_TRAINS) {
                    printf("Invalid input for train number. Please try again.\n");
                    while (getchar() != '\n'); 
                    continue;   
                }
                displayAvailableSeats(trainChoice);
                break;
            case 3:
                printf("\nEnter the train number: ");
                if (scanf("%d", &trainChoice) != 1 || trainChoice < 1 || trainChoice > MAX_TRAINS) {
                    printf("Invalid input for train number. Please try again.\n");
                    while (getchar() != '\n');  
                    continue;   
                }
                bookTicket(trainChoice);
                break;
            case 4:
                printf("\nEnter the train number: ");
                if (scanf("%d", &trainChoice) != 1 || trainChoice < 1 || trainChoice > MAX_TRAINS) {
                    printf("Invalid input for train number. Please try again.\n");
                    while (getchar() != '\n');  
                    continue;   
                }
                displayReservationStatus(trainChoice);
                break;
            case 5:
                showAllReservations();
                break;
            case 6:
                printf("\nEnter the train number: ");
                if (scanf("%d", &trainChoice) != 1 || trainChoice < 1 || trainChoice > MAX_TRAINS){
                    printf("Invalid input for train number. Please try again.\n");
                    while (getchar() != '\n'); 
                    continue; 
                }
                showBookedTicket(trainChoice);
                break;
            case 7:
                printf("Exiting the program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}


