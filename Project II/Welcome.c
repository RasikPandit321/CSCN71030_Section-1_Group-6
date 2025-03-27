#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "Welcome.h"

#define TOTAL_TABLES 10
bool tables[TOTAL_TABLES] = { false }; // Track which tables are assigned

void openMenuModule(); // Placeholder function

// Function to display welcome message
void displayWelcomeMessage() {
    printf("=====================================\n");
    printf("       Welcome to Byte and Bite!    \n");
    printf("       Food that tells the story    \n");
    printf("=====================================\n");
    printf("Please choose a service option:\n");
    printf("1. Dine-In\n");
    printf("2. Pick-Up\n");
    printf("3. Delivery\n");
    printf("4. Exit\n");
}

// Function to get user selection
int getUserSelection() {
    int selection;
    while (1) {
        printf("\nEnter your choice (1-4): ");
        if (scanf_s("%d", &selection) != 1) {
            printf("Invalid input! Please enter a number between 1-4.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }
        if (selection >= 1 && selection <= 4) return selection;
        printf("Invalid choice! Please select between 1-4.\n");
    }
}

// Function to assign a random available table
int assignRandomTable() {
    int attempts = 0;
    while (attempts < 20) { // try max 20 times to avoid infinite loop
        int randomIndex = rand() % TOTAL_TABLES; // random 0–9
        if (!tables[randomIndex]) {
            tables[randomIndex] = true;
            return randomIndex + 1; // return table number (1–10)
        }
        attempts++;
    }
    return -1; // all tables might be full
}

// Function to handle navigation
void navigateSelection(int selection) {
    switch (selection) {
    case 1: {
        printf("\nYou selected Dine-In.\n");
        int tableNumber = assignRandomTable();
        if (tableNumber == -1) {
            printf("All tables are currently occupied. Please wait for couple of minutes or you can try Pick-Up or Delivery.\n");
        }
        else {
            printf("Table %d has been assigned to you. Redirecting to the menu...\n", tableNumber);
            openMenuModule();
        }
        break;
    }
    case 2:
        printf("\nYou selected Pick-Up. Processing your order...\n");
        openMenuModule();
        break;
    case 3:
        printf("\nYou selected Delivery. Please enter your address details...\n");
        openMenuModule();
        break;
    case 4:
        printf("\nThank you for visiting Byte and Bite! Have a great day!\n");
        exit(0); //Proper exit added
        break;
    default:
        printf("\nUnexpected error occurred.\n");
        break;
    }
}

// Placeholder for menu module
void openMenuModule() {
    printf("Opening Menu Module...\n");
}



