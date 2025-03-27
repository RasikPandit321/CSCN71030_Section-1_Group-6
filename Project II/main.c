#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

int main() {
    int choice;
    char category[20];
    char itemName[50], itemDescription[250];
    float itemPrice;
    int itemID;

    // Ensure all menu files exist before using them
    CreateMenuFileIfNotExists();

    do {
        printf("\n==== Restaurant Menu Management ====\n");
        printf("1. Add a Menu Item\n");
        printf("2. Remove a Menu Item\n");
        printf("3. Update a Menu Item\n");
        printf("4. Display Appetizers\n");
        printf("5. Display Main Course\n");
        printf("6. Display Desserts\n");
        printf("7. Display Drinks\n");
        printf("8. Search for Items by Category\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer

        switch (choice) {
        case 1:
            // Add a menu item
            printf("Enter item name: ");
            fgets(itemName, sizeof(itemName), stdin);
            itemName[strcspn(itemName, "\n")] = 0;  // Remove newline

            printf("Enter description: ");
            fgets(itemDescription, sizeof(itemDescription), stdin);
            itemDescription[strcspn(itemDescription, "\n")] = 0;

            printf("Enter price: ");
            scanf_s("%f", &itemPrice);
            while (getchar() != '\n');  // Clear input buffer

            printf("Enter category (Appetizers, Main Course, Desserts, Drinks): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            if (AddMenuItem(itemName, itemDescription, itemPrice, category))
                printf("Item added successfully!\n");
            else
                printf("Failed to add item. Menu may be full or invalid category.\n");
            break;

        case 2:
            // Remove a menu item
            printf("Enter category of the item to remove: ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            printf("Enter item ID to remove: ");
            scanf_s("%d", &itemID);
            while (getchar() != '\n');  // Clear input buffer

            if (RemoveMenuItem(itemID, GetCategoryFile(category)))
                printf("Item removed successfully!\n");
            else
                printf("Failed to remove item. Check ID or category.\n");
            break;

        case 3:
            // Update a menu item
            printf("Enter category of the item to update: ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            printf("Enter item ID to update: ");
            scanf_s("%d", &itemID);
            while (getchar() != '\n');  // Clear input buffer

            printf("Enter new item name: ");
            fgets(itemName, sizeof(itemName), stdin);
            itemName[strcspn(itemName, "\n")] = 0;

            printf("Enter new description: ");
            fgets(itemDescription, sizeof(itemDescription), stdin);
            itemDescription[strcspn(itemDescription, "\n")] = 0;

            printf("Enter new price: ");
            scanf_s("%f", &itemPrice);
            while (getchar() != '\n');  // Clear input buffer

            if (UpdateMenuItem(itemID, itemName, itemDescription, itemPrice, category, GetCategoryFile(category)))
                printf("Item updated successfully!\n");
            else
                printf("Failed to update item. Check ID or category.\n");
            break;

        case 4:
            // Display appetizers
            DisplayMenu(FILE_APPETIZERS);
            break;
        case 5:
            // Display main course
            DisplayMenu(FILE_MAIN_COURSE);
            break;
        case 6:
            // Display desserts
            DisplayMenu(FILE_DESSERTS);
            break;
        case 7:
            // Display drinks
            DisplayMenu(FILE_DRINKS);
            break;

        case 8:
            // Search for menu items by category
            printf("Enter category to search (Appetizers, Main Course, Desserts, Drinks): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;

            if (!GetMenuItem(category))
                printf("No items found in this category.\n");
            break;

        case 9:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice! Please enter a number between 1-9.\n");
        }
    } while (choice != 9);

    return 0;
}
