#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "management.h"
#include "display.h"
#include "reports.h"

void cancelBooking(void) {
    printf("\n=========================================\n");
    printf("        ---- CANCEL BOOKING ----         \n");
    printf("=========================================\n");
    
    displayShowtimes();

    printf("\nEnter Movie ID (1-%d): ", NUM_MOVIES);
    int mIndex = getValidatedInt(1, NUM_MOVIES) - 1;

    printf("Enter Showtime (1-%d): ", NUM_SHOWTIMES);
    int sIndex = getValidatedInt(1, NUM_SHOWTIMES) - 1;

    Showtime *show = &movies[mIndex].showtimes[sIndex];

    char rowChar;
    int r, c;
    while (1) {
        printf("Enter Row to Cancel (A-%c): ", 'A' + ROWS - 1);
        if (scanf(" %c", &rowChar) != 1) {
            clearInputBuffer();
            printf("[Error] Invalid input. Try again.\n");
            continue;
        }
        clearInputBuffer();
        rowChar = toupper(rowChar);
        r = rowChar - 'A';
        if (r >= 0 && r < ROWS) break;
        printf("[Error] Invalid row. Please try again.\n");
    }

    printf("Enter Seat Number to Cancel (1-%d): ", COLS);
    c = getValidatedInt(1, COLS) - 1;

    if (!show->seats[r][c].isBooked) {
        printf("\n[Error] Seat %c%d is not currently booked!\n", rowChar, c + 1);
        printf("=========================================\n");
        return;
    }

    show->ticketsSold--;
    show->totalRevenue -= show->seats[r][c].pricePaid;

    show->seats[r][c].isBooked = 0;
    show->seats[r][c].pricePaid = 0.0f;
    show->seats[r][c].isStudent = 0;
    show->seats[r][c].isSenior = 0;
    strcpy(show->seats[r][c].customerName, "");

    printf("\n[Success] Booking for seat %c%d has been canceled and revenue updated.\n", rowChar, c + 1);
    printf("=========================================\n");
}

void searchBooking(void) {
    printf("\n=========================================\n");
    printf("         ---- SEARCH BOOKING ----        \n");
    printf("=========================================\n");
    printf("Search by:\n1. Customer Name\n2. Seat Number\nEnter choice (1-2): ");
    int choice = getValidatedInt(1, 2);

    int found = 0;

    if (choice == 1) {
        char searchName[50];
        printf("Enter Customer Name to search: ");
        if (fgets(searchName, sizeof(searchName), stdin) != NULL) {
            searchName[strcspn(searchName, "\n")] = 0;
        }

        printf("\n--- Search Results for '%s' ---\n", searchName);
        for (int i = 0; i < NUM_MOVIES; i++) {
            for (int j = 0; j < NUM_SHOWTIMES; j++) {
                Showtime *show = &movies[i].showtimes[j];
                for (int r = 0; r < ROWS; r++) {
                    for (int c = 0; c < COLS; c++) {
                        if (show->seats[r][c].isBooked && 
                            stringCompareIgnoreCase(show->seats[r][c].customerName, searchName) == 0) {
                            printf("Movie: %s | Showtime: %s | Seat: %c%d | Price Paid: Rs. %.2f\n",
                                   movies[i].title, show->time, 'A' + r, c + 1, show->seats[r][c].pricePaid);
                            found = 1;
                        }
                    }
                }
            }
        }
    } else {
        displayShowtimes();
        printf("Enter Movie ID (1-%d): ", NUM_MOVIES);
        int mIndex = getValidatedInt(1, NUM_MOVIES) - 1;
        printf("Enter Showtime (1-%d): ", NUM_SHOWTIMES);
        int sIndex = getValidatedInt(1, NUM_SHOWTIMES) - 1;

        Showtime *show = &movies[mIndex].showtimes[sIndex];

        char rowChar;
        int r, c;
        while (1) {
            printf("Enter Row (A-%c): ", 'A' + ROWS - 1);
            if (scanf(" %c", &rowChar) != 1) {
                clearInputBuffer();
                printf("[Error] Invalid input. Try again.\n");
                continue;
            }
            clearInputBuffer();
            rowChar = toupper(rowChar);
            r = rowChar - 'A';
            if (r >= 0 && r < ROWS) break;
            printf("[Error] Invalid row.\n");
        }
        printf("Enter Seat Number (1-%d): ", COLS);
        c = getValidatedInt(1, COLS) - 1;

        printf("\n--- Search Results for Seat %c%d ---\n", rowChar, c + 1);
        if (show->seats[r][c].isBooked) {
            printf("Movie: %s | Showtime: %s | Customer: %s | Price Paid: Rs. %.2f\n",
                   movies[mIndex].title, show->time, show->seats[r][c].customerName, show->seats[r][c].pricePaid);
            found = 1;
        }
    }

    if (!found) {
        printf("[Info] No matching bookings found.\n");
    }
    printf("=========================================\n");
}
