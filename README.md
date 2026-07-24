# Movie Ticket Booking System

A modular console-based Movie Ticket Booking System written in C as a collaborative group project.

## 📂 Project Structure & Module Division

To facilitate seamless Git branching and individual contributions, the project is broken down into 5 independent modules assigned to team members:

| Member | Assigned Files | Core Responsibilities |
| :--- | :--- | :--- |
| **Member 1** | `main.c` | Program entry point, main menu loop, and routing user choices (1–7). |
| **Member 2** | `display.h`, `display.c` | System initialization, movie/showtime setup, displaying showtimes, and rendering the interactive seat map. |
| **Member 3** | `reservation.h`, `reservation.c` | Multi-seat booking workflow, seat validation, tier pricing, and discount applications. |
| **Member 4** | `management.h`, `management.c` | Canceling existing bookings, updating revenue/ticket counts, and searching by name or seat. |
| **Member 5** | `reports.h`, `reports.c` | Grand total revenue reporting, input validation helpers (`getValidatedInt`), buffer clearing, and screen utilities. |

---

## 🛠️ System Architecture

```text
                  [ main.c ] (Member 1)
           /         |         \          \
          /          |          \          \
     [display.c] [reservation.c] [management.c] [reports.c]
     (Member 2)   (Member 3)     (Member 4)     (Member 5)
