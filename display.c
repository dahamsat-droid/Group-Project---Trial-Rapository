#include <stdio.h>
#include <string.h>
#include "display.h"
#include "reports.h"

void initializeSystem(void) {
    const char *movieTitles[NUM_MOVIES] = {
        "Jurassic World Rebirth [English]", 
        "Dhurandhar: The Revenge [Hindi]", 
        "Neera [Sinhala]"
    };
    const char *showtimesList[NUM_SHOWTIMES] = {"10:30 AM", "06:30 PM"};

    for (int i = 0; i < NUM_MOVIES; i++) {
        movies[i].id = i + 1;
        strcpy(movies[i].title, movieTitles[i]);

        for (int j = 0; j < NUM_SHOWTIMES; j++) {
            strcpy(movies[i].showtimes[j].time, showtimesList[j]);
            movies[i].showtimes[j].ticketsSold = 0;
            movies[i].showtimes[j].totalRevenue = 0.0f;

            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    movies[i].showtimes[j].seats[r][c].isBooked = 0;
                    movies[i].showtimes[j].seats[r][c].pricePaid = 0.0f;
                    movies[i].showtimes[j].seats[r][c].isStudent = 0;
                    movies[i].showtimes[j].seats[r][c].isSenior = 0;
                    strcpy(movies[i].showtimes[j].seats[r][c].customerName, "");
                }
            }
        }
    }
}

void displayShowtimes(void) {
    printf("\n=========================================\n");
    printf("         ---- AVAILABLE SHOWTIMES ----     \n");
    printf("=========================================\n");
    for (int i = 0; i < NUM_MOVIES; i++) {
        printf("\n[%d] %s\n", movies[i].id, movies[i].title);
        for (int j = 0; j < NUM_SHOWTIMES; j++) {
            printf("    Showtime %d: %s\n", j + 1, movies[i].showtimes[j].time);
        }
    }
    printf("-----------------------------------------\n");
}

void viewSeatMap(void) {
    displayShowtimes();
    
    printf("\nEnter Movie ID (1-%d): ", NUM_MOVIES);
    int mIndex = getValidatedInt(1, NUM_MOVIES) - 1;

    printf("Enter Showtime (1-%d): ", NUM_SHOWTIMES);
    int sIndex = getValidatedInt(1, NUM_SHOWTIMES) - 1;

    Showtime *show = &movies[mIndex].showtimes[sIndex];

    printf("\n=========================================\n");
    printf("            ---- SEAT MAP ----           \n");
    printf("=========================================\n");
    printf(" Movie: %s | Time: %s\n", movies[mIndex].title, show->time);
    printf(" Legend: [.] Free | [X] Booked\n");
    printf(" Tiers: Rows A-B (Regular), Rows C-D (Premium), Row E (VIP)\n");
    printf("-----------------------------------------\n");
    printf("    ");
    for (int c = 0; c < COLS; c++) printf("%2d ", c + 1);
    printf("\n");

    for (int r = 0; r < ROWS; r++) {
        char rowLetter = 'A' + r;
        printf(" %c  ", rowLetter);
        for (int c = 0; c < COLS; c++) {
            if (show->seats[r][c].isBooked) {
                printf(" X ");
            } else {
                printf(" . ");
            }
        }
        if (r < 2) printf(" (Regular - Rs. 500)");
        else if (r < 4) printf(" (Premium - Rs. 750)");
        else printf(" (VIP - Rs. 1000)");
        printf("\n");
    }
    printf("=========================================\n");
}
