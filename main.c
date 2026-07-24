#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "reservation.h"
#include "management.h"
#include "reports.h"

// Global Data Setup Definition
Movie movies[NUM_MOVIES];

int main(void) {
    initializeSystem();
    int choice;

    do {
        printf("\n=========================================\n");
        printf("     MOVIE TICKET BOOKING SYSTEM         \n");
        printf("=========================================\n");
        printf("1. View Showtimes\n");
        printf("2. View Seat Map\n");
        printf("3. Book a Seat\n");
        printf("4. Cancel a Booking\n");
        printf("5. Search Booking\n");
        printf("6. View Revenue Report\n");
        printf("7. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice (1-7): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input. Please enter a number between 1 and 7.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                displayShowtimes();
                pauseScreen();
                break;
            case 2:
                viewSeatMap();
                pauseScreen();
                break;
            case 3:
                bookSeat();
                pauseScreen();
                break;
            case 4:
                cancelBooking();
                pauseScreen();
                break;
            case 5:
                searchBooking();
                pauseScreen();
                break;
            case 6:
                viewRevenueReport();
                pauseScreen();
                break;
            case 7:
                printf("\nExiting program. Thank you!\n");
                break;
            default:
                printf("\n[Error] Invalid choice. Please select an option from 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}
