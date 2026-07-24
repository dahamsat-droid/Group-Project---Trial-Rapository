#ifndef DISPLAY_H
#define DISPLAY_H

#define NUM_MOVIES 3
#define NUM_SHOWTIMES 2
#define ROWS 5
#define COLS 10

typedef struct {
    char customerName[50];
    int isBooked;
    float pricePaid;
    int isStudent;
    int isSenior;
} Seat;

typedef struct {
    char time[20];
    Seat seats[ROWS][COLS];
    int ticketsSold;
    float totalRevenue;
} Showtime;

typedef struct {
    int id;
    char title[50];
    Showtime showtimes[NUM_SHOWTIMES];
} Movie;

extern Movie movies[NUM_MOVIES];

void initializeSystem(void);
void displayShowtimes(void);
void viewSeatMap(void);

#endif
