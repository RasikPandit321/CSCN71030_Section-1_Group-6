
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
// Function to navigate based on user selection
void navigateSelection(int selection)
{
    switch (selection)
    {
    case 1:
        printf("\nYou selected Dine-In. Redirecting to the menu...\n");
        // Call menu module function (if implemented)
        break;
    case 2:
        printf("\nYou selected Pick-Up. Processing your order...\n");
        // Call order processing module
        break;
    case 3:
        printf("\nYou selected Delivery. Please enter your address details...\n");
        // Call delivery module
        break;
    case 4:
        printf("\nThank you for visiting Byte and Bite! Have a great day!\n");
        break;
    default:
        printf("\nUnexpected error occurred.\n");
        break;
    }
}



