# 🎬 Movie Ticket Booking System

A modular, console-based **Movie Ticket Booking System** written in C. Developed as a collaborative multi-member group project utilizing Git branches and modular software design principles.

---

## 👥 Group Project Division & File Mapping

| Member | Assigned Files | Core Responsibilities |
| :--- | :--- | :--- |
| **Member 1** | `main.c` | Program entry point, main menu loop, and user choice routing (1–7). |
| **Member 2** | `display.h`, `display.c` | System initialization, movie/showtime setups, displaying showtimes, and rendering the interactive seat map. |
| **Member 3** | `reservation.h`, `reservation.c` | Multi-seat booking workflow, seat availability verification, tier pricing, and discount applications. |
| **Member 4** | `management.h`, `management.c` | Booking cancellation workflow, ticket count/revenue adjustments, and searching by customer name or seat. |
| **Member 5** | `reports.h`, `reports.c` | Grand total revenue reports, input validation helpers (`getValidatedInt`), buffer clearing, and screen pauses. |

---

##  System Architecture & File Flow

The application is broken down into independent modules that link directly back to the core execution engine:

```text
                        ┌────────────────────────┐
                        │        main.c          │ ◄─── (Member 1)
                        │  (Program Entry Point) │
                        └───────────┬────────────┘
         ┌──────────────────────────┼──────────────────────────┐
         ▼                          ▼                          ▼
┌──────────────────┐       ┌──────────────────┐       ┌──────────────────┐
│    display.c     │       │  reservation.c   │       │  management.c    │
│    (Member 2)    │       │    (Member 3)    │       │    (Member 4)    │
└──────────────────┘       └──────────────────┘       └──────────────────┘
         │                          │                          │
         └──────────────────────────┼──────────────────────────┘
                                    ▼
                           ┌──────────────────┐
                           │    reports.c     │ ◄─── (Member 5 - Utility & Reports)
                           └──────────────────┘

