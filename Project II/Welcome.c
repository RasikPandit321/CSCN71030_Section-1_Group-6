
#include <stdio.h>
#include "Welcome.h"

// Function to display the welcome message and service options
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

// Function to get and validate user selection
int getUserSelection() {
    int selection;

    while (1) {
        printf("\nEnter your choice (1-4): ");
        if (scanf_s("%d", &selection) != 1) {
            printf("Invalid input! Please enter a number between 1-4.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        if (selection >= 1 && selection <= 4) {
            return selection;
        }
        printf("Invalid choice! Please select between 1-4.\n");
    }
}



