#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "welcome.h"
#include "menu.h"
#include "order.h"
#include "billing.h"
#include "order_flow.h"


#define TOTAL_TABLES 10

bool tables[TOTAL_TABLES] = { false };

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

char getYesNoInput(const char* prompt) {
    char response;
    while (1) {
        printf("%s (Y/N): ", prompt);
        if (scanf_s(" %c", &response, 1) == 1) {
            response = toupper(response);
            if (response == 'Y' || response == 'N') return response;
        }
        printf("Invalid input! Please enter Y or N.\n");
        while (getchar() != '\n');
    }
}

int getUserSelection() {
    char inputBuffer[10];
    int selection;

    while (1) {
        printf("\nEnter your choice (1-4): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = 0;

        char* endptr;
        selection = strtol(inputBuffer, &endptr, 10);

        if (endptr == inputBuffer || *endptr != '\0' || selection < 1 || selection > 4) {
            printf("Invalid input! Please enter a number between 1 and 4.\n");
        }
        else {
            return selection;
        }
    }
}


int assignRandomTable() {
    for (int i = 0; i < TOTAL_TABLES; i++) {
        if (!tables[i]) {
            tables[i] = true;
            return i + 1;
        }
    }
    return -1;
}

void navigateSelection(int selection) {
    switch (selection) {
    case 1:
        printf("\nYou selected Dine-In.\n");
        int tableNumber = assignRandomTable();
        if (tableNumber == -1) {
            printf("All tables are currently occupied. Please wait or try Pick-Up or Delivery.\n");
        }
        else {
            printf("Table %d has been assigned to you.\n", tableNumber);
            startCustomerOrder("Dine-In");
        }
        break;
    case 2:
        printf("\nYou selected Pick-Up.\n");
        startCustomerOrder("Pick-Up");
        break;
    case 3:
        printf("\nYou selected Delivery.\n");
        startCustomerOrder("Delivery");
        break;
    case 4:
        printf("\nThank you for visiting Byte and Bite! Have a great day!\n");
        exit(0);
    }
}

void runCustomerVersion() {
    displayWelcomeMessage();
    int selection = getUserSelection();
    navigateSelection(selection);
}

void runStaffVersion() {
    printf("Welcome, staff member!\n");
    CreateMenuFileIfNotExists();
    DisplayCustomerMenu();
}
