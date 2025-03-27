#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Global variables
MenuItem menu[MAX_MENU_ITEMS];
int menuItemCount = 0;

// Load menu items from file
int LoadMenuFromFile(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Error opening file: %s\n", filename);
        return 0;  // File not found
    }

    menuItemCount = 0;
    while (fscanf_s(file, "%d,%49[^,],%249[^,],%f,%19[^\n]",
        &menu[menuItemCount].itemID,
        menu[menuItemCount].itemName,
        (unsigned int)sizeof(menu[menuItemCount].itemName),
        menu[menuItemCount].itemDescription,
        (unsigned int)sizeof(menu[menuItemCount].itemDescription),
        &menu[menuItemCount].itemPrice,
        menu[menuItemCount].itemCategory,
        (unsigned int)sizeof(menu[menuItemCount].itemCategory)) == 5) {
        menuItemCount++;
    }

    fclose(file);
    return 1;
}

// Save menu items to file
int SaveMenuToFile(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    for (int i = 0; i < menuItemCount; i++) {
        fprintf(file, "%d,%s,%s,%.2f,%s\n",
            menu[i].itemID,
            menu[i].itemName,
            menu[i].itemDescription,
            menu[i].itemPrice,
            menu[i].itemCategory);
    }

    fclose(file);
    return 1;
}

// Add a menu item to the correct category file
int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]) {
    if (menuItemCount >= MAX_MENU_ITEMS) return 0;  // Menu full

    if (itemName[0] == '\0' || itemDescription[0] == '\0' || itemCategory[0] == '\0') return 0;  // Invalid input

    const char* filename = GetCategoryFile(itemCategory);
    if (!filename) return 0;  // Invalid category

    int newID = (menuItemCount == 0) ? 1 : menu[menuItemCount - 1].itemID + 1;
    menu[menuItemCount].itemID = newID;
    strcpy_s(menu[menuItemCount].itemName, sizeof(menu[menuItemCount].itemName), itemName);
    strcpy_s(menu[menuItemCount].itemDescription, sizeof(menu[menuItemCount].itemDescription), itemDescription);
    menu[menuItemCount].itemPrice = itemPrice;
    strcpy_s(menu[menuItemCount].itemCategory, sizeof(menu[menuItemCount].itemCategory), itemCategory);

    menuItemCount++;
    return SaveMenuToFile(filename);
}

// Remove a menu item
int RemoveMenuItem(int itemID, const char* filename) {
    LoadMenuFromFile(filename);

    int found = 0;
    for (int i = 0; i < menuItemCount; i++) {
        if (menu[i].itemID == itemID) {
            found = 1;
            for (int j = i; j < menuItemCount - 1; j++) {
                menu[j] = menu[j + 1];
            }
            menuItemCount--;
            break;
        }
    }

    return found ? SaveMenuToFile(filename) : 0;
}

// Update a menu item
int UpdateMenuItem(int itemID, char itemName[], char itemDescription[], float itemPrice, char itemCategory[], const char* filename) {
    LoadMenuFromFile(filename);

    for (int i = 0; i < menuItemCount; i++) {
        if (menu[i].itemID == itemID) {
            strcpy_s(menu[i].itemName, sizeof(menu[i].itemName), itemName);
            strcpy_s(menu[i].itemDescription, sizeof(menu[i].itemDescription), itemDescription);
            menu[i].itemPrice = itemPrice;
            strcpy_s(menu[i].itemCategory, sizeof(menu[i].itemCategory), itemCategory);
            return SaveMenuToFile(filename);
        }
    }

    return 0;
}

// Display menu items
void DisplayMenu(const char* filename) {
    LoadMenuFromFile(filename);

    if (menuItemCount == 0) {
        printf("No menu items available in this category.\n");
        return;
    }

    printf("\n=== Menu Items from %s ===\n", filename);
    for (int i = 0; i < menuItemCount; i++) {
        printf("ID: %d, Name: %s, Price: $%.2f\nDescription: %s\n",
            menu[i].itemID, menu[i].itemName,
            menu[i].itemPrice, menu[i].itemDescription);
    }
}

// Retrieve and display menu items by category
int GetMenuItem(char itemCategory[]) {
    const char* filename = GetCategoryFile(itemCategory);
    if (!filename) return 0;  // Invalid category

    DisplayMenu(filename);
    return 1;
}

// Function to create category menu files if they do not exist
void CreateMenuFileIfNotExists() {
    const char* filenames[] = { FILE_APPETIZERS, FILE_MAIN_COURSE, FILE_DESSERTS, FILE_DRINKS };

    for (int i = 0; i < 4; i++) {
        FILE* file;
        if (fopen_s(&file, filenames[i], "r") != 0) {
            // If the file does not exist, create it with default items
            if (fopen_s(&file, filenames[i], "w") != 0) {
                printf("Error creating menu file: %s\n", filenames[i]);
                continue;
            }
            fclose(file);
        }
        else {
            fclose(file);  // File already exists, no action needed
        }
    }
}
