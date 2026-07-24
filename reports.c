#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "reports.h"
#include "display.h"

void viewRevenueReport(void) {
    printf("\n=========================================\n");
    printf("        ---- REVENUE REPORT ----         \n");
    printf("=========================================\n");
    float grandTotal = 0.0f;
    int totalTicketsAll = 0;

    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("\nMovie: %s\n", movies[i].title);
        for (int j = 0; j < NUM_SHOWTIMES; j++) {
            Showtime *show = &movies[i].showtimes[j];
            printf("  - Showtime [%s]: Tickets Sold = %d | Revenue = Rs. %.2f\n",
                   show->time, show->ticketsSold, show->totalRevenue);
            grandTotal += show->totalRevenue;
            totalTicketsAll += show->ticketsSold;
        }
    }
    printf("-----------------------------------------\n");
    printf("Total Tickets Sold Across All Shows: %d\n", totalTicketsAll);
    printf("Grand Total Revenue: Rs. %.2f\n", grandTotal);
    printf("=========================================\n");
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pauseScreen(void) {
    printf("\nPress Enter to return to the main menu...");
    clearInputBuffer();
}

int getValidatedInt(int min, int max) {
    int value;
    while (1) {
        if (scanf("%d", &value) != 1) {
            printf("[Error] Invalid input. Please enter a valid number: ");
            clearInputBuffer();
        } else if (value < min || value > max) {
            printf("[Error] Value out of range (%d-%d). Try again: ", min, max);
        } else {
            clearInputBuffer();
            return value;
        }
    }
}

int stringCompareIgnoreCase(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}
