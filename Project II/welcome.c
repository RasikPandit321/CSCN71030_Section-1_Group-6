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

    int choice;
    char input[100];

    while (1) {
        printf("\n==== Staff Menu ====\n");
        printf("1. View Menu by Category\n");
        printf("2. Add Menu Item\n");
        printf("3. Update Menu Item\n");
        printf("4. Remove Menu Item\n");
        printf("5. Exit Staff Mode\n");
        printf("Enter your choice: ");

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        if (choice == 1) {
            char category[20];
            printf("Enter category (Appetizers, Main Course, Desserts, Drinks): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            if (!GetMenuItem(category)) {
                printf("Invalid category or no items found.\n");
            }
        }
        else if (choice == 2) {
            char name[50], description[250], category[20];
            float price;

            printf("Enter item name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            printf("Enter item description: ");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = 0;

            printf("Enter item price: ");
            fgets(input, sizeof(input), stdin);
            price = strtof(input, NULL);

            printf("Enter category (Appetizers, Main Course, Desserts, Drinks): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            if (AddMenuItem(name, description, price, category)) {
                printf("Item added successfully!\n");
            }
            else {
                printf("Failed to add item.\n");
            }

        }
        else if (choice == 3) {
            int id;
            char name[50], description[250], category[20];
            float price;

            printf("Enter item ID to update: ");
            fgets(input, sizeof(input), stdin);
            id = atoi(input);

            printf("Enter new name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            printf("Enter new description: ");
            fgets(description, sizeof(description), stdin);
            description[strcspn(description, "\n")] = 0;

            printf("Enter new price: ");
            fgets(input, sizeof(input), stdin);
            price = strtof(input, NULL);

            printf("Enter new category: ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            const char* file = GetCategoryFile(category);
            if (UpdateMenuItem(id, name, description, price, category, file)) {
                printf("Item updated successfully.\n");
            }
            else {
                printf("Failed to update item.\n");
            }

        }
        else if (choice == 4) {
            int id;
            char category[20];

            printf("Enter item ID to remove: ");
            fgets(input, sizeof(input), stdin);
            id = atoi(input);

            printf("Enter category of the item: ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            const char* file = GetCategoryFile(category);
            if (RemoveMenuItem(id, file)) {
                printf("Item removed successfully.\n");
            }
            else {
                printf("Failed to remove item.\n");
            }

        }
        else if (choice == 5) {
            printf("Exiting staff mode...\n");
            break;
        }
        else {
            printf("Invalid choice! Please select between 1 and 5.\n");
        }
    }
}

