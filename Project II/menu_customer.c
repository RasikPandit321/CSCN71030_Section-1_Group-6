#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Function to display the customer-facing menu
void DisplayCustomerMenu() {
    int choice;
    char category[20];

    do {
        printf("\n==== Customer Menu ====\n");
        printf("1. View Appetizers\n");
        printf("2. View Main Course\n");
        printf("3. View Drinks\n");
        printf("4. View Desserts\n");
        printf("5. Search for Items by Category\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer

        switch (choice) {
        case 1:
            // Display Appetizers
            DisplayMenu(FILE_APPETIZERS);
            break;
        case 2:
            // Display Main Course
            DisplayMenu(FILE_MAIN_COURSE);
            break;
        case 3:
            // Display Drinks
            DisplayMenu(FILE_DRINKS);
            break;
        case 4:
            // Display Desserts
            DisplayMenu(FILE_DESSERTS);
            break;
        case 5:
            // Search for items by category
            printf("Enter category to search (Appetizers, Main Course, Desserts, Drinks): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            if (!GetMenuItem(category)) {
                printf("No items found in this category.\n");
            }
            break;
        case 6:
            printf("Exiting customer menu...\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1-6.\n");
        }
    } while (choice != 6);
}

// This function can be expanded to allow customers to make orders, rate items, etc.
// For now, it is set to handle the display and search functionalities for the menu.
