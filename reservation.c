#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "reservation.h"
#include "display.h"
#include "reports.h"

void bookSeat(void) {
    printf("\n=========================================\n");
    printf("          ---- BOOK SEAT ----            \n");
    printf("=========================================\n");
    
    displayShowtimes();

    printf("\nEnter Movie ID (1-%d): ", NUM_MOVIES);
    int mIndex = getValidatedInt(1, NUM_MOVIES) - 1;

    printf("Enter Showtime (1-%d): ", NUM_SHOWTIMES);
    int sIndex = getValidatedInt(1, NUM_SHOWTIMES) - 1;

    Showtime *show = &movies[mIndex].showtimes[sIndex];

    printf("How many seats are being booked in this single transaction?: ");
    int numSeats = getValidatedInt(1, 50);

    char name[50];
    printf("Enter Customer Name: ");
    if (fgets(name, sizeof(name), stdin) != NULL) {
        name[strcspn(name, "\n")] = 0;
    }

    int isStudent = 0, isSenior = 0;
    printf("Is the customer a Student? (1: Yes, 0: No): ");
    isStudent = getValidatedInt(0, 1);

    if (!isStudent) {
        printf("Is the customer a Senior Citizen? (1: Yes, 0: No): ");
        isSenior = getValidatedInt(0, 1);
    }

    int selectedRows[50];
    int selectedCols[50];
    float selectedPrices[50];

    for (int i = 0; i < numSeats; i++) {
        printf("\n--- Selecting Seat %d of %d ---\n", i + 1, numSeats);
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
            printf("[Error] Invalid row. Please try again.\n");
        }

        printf("Enter Seat Number (1-%d): ", COLS);
        c = getValidatedInt(1, COLS) - 1;

        if (show->seats[r][c].isBooked) {
            printf("[Error] Seat %c%d is already taken! Choose a different seat.\n", rowChar, c + 1);
            i--; 
            continue;
        }

        int duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (selectedRows[j] == r && selectedCols[j] == c) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            printf("[Error] You already selected seat %c%d in this transaction!\n", rowChar, c + 1);
            i--;
            continue;
        }

        float basePrice = 500.0f;
        if (r >= 2 && r < 4) basePrice = 750.0f;
        else if (r == 4) basePrice = 1000.0f;

        float finalPrice = basePrice;

        if (isStudent) {
            finalPrice -= (basePrice * 0.10f);
        } else if (isSenior) {
            finalPrice -= (basePrice * 0.20f);
        }

        if (numSeats >= 4) {
            finalPrice -= (basePrice * 0.10f);
        }

        selectedRows[i] = r;
        selectedCols[i] = c;
        selectedPrices[i] = finalPrice;
    }

    for (int i = 0; i < numSeats; i++) {
        int r = selectedRows[i];
        int c = selectedCols[i];
        show->seats[r][c].isBooked = 1;
        strcpy(show->seats[r][c].customerName, name);
        show->seats[r][c].pricePaid = selectedPrices[i];
        show->seats[r][c].isStudent = isStudent;
        show->seats[r][c].isSenior = isSenior;

        show->ticketsSold++;
        show->totalRevenue += selectedPrices[i];
    }

    printf("\n[Success] Successfully booked %d seat(s) for %s!\n", numSeats, name);
    printf("=========================================\n");
}
