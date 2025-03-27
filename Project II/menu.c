#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// **Global variables** (shared across files)
MenuItem menu[MAX_MENU_ITEMS];
int menuItemCount = 0;

// Function to determine the file based on category
const char* GetCategoryFile(const char* category) {
    if (strcmp(category, "Appetizers") == 0) return FILE_APPETIZERS;
    if (strcmp(category, "Main Course") == 0) return FILE_MAIN_COURSE;
    if (strcmp(category, "Desserts") == 0) return FILE_DESSERTS;
    if (strcmp(category, "Drinks") == 0) return FILE_DRINKS;
    return NULL;  // Invalid category
}

// Load menu items from file
int LoadMenuFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);  // Debug print
        return 0;  // File not found
    }

    menuItemCount = 0;
    while (fscanf(file, "%d,%49[^,],%249[^,],%f,%19[^\n]",
        &menu[menuItemCount].itemID,
        menu[menuItemCount].itemName,
        menu[menuItemCount].itemDescription,
        &menu[menuItemCount].itemPrice,
        menu[menuItemCount].itemCategory) == 5) {

        printf("Item Loaded: ID = %d, Name = %s\n", menu[menuItemCount].itemID, menu[menuItemCount].itemName);
        menuItemCount++;
    }

    printf("Loaded %d menu items from file.\n", menuItemCount);  // Debug print
    fclose(file);
    return 1;
}



// Save menu items to file
int SaveMenuToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return 0;

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
    strcpy(menu[menuItemCount].itemName, itemName);
    strcpy(menu[menuItemCount].itemDescription, itemDescription);
    menu[menuItemCount].itemPrice = itemPrice;
    strcpy(menu[menuItemCount].itemCategory, itemCategory);

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
            strcpy(menu[i].itemName, itemName);
            strcpy(menu[i].itemDescription, itemDescription);
            menu[i].itemPrice = itemPrice;
            strcpy(menu[i].itemCategory, itemCategory);
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
        FILE* file = fopen(filenames[i], "r");

        // If the file does not exist, create it with default items
        if (!file) {
            file = fopen(filenames[i], "w");
            if (!file) {
                printf("Error creating menu file: %s\n", filenames[i]);
                continue;
            }

            // Add default items based on category
            if (strcmp(filenames[i], FILE_APPETIZERS) == 0) {
                fprintf(file, "1,Samosa,Crispy fried pastry stuffed with spicy potatoes,2.50,Appetizers\n");
                fprintf(file, "2,Spring Rolls,Vegetable-stuffed crispy rolls,3.00,Appetizers\n");
            }
            else if (strcmp(filenames[i], FILE_MAIN_COURSE) == 0) {
                fprintf(file, "3,Butter Chicken,Creamy tomato-based chicken curry,12.00,Main Course\n");
                fprintf(file, "4,Chow Mein,Stir-fried noodles with vegetables and meat,10.00,Main Course\n");
            }
            else if (strcmp(filenames[i], FILE_DESSERTS) == 0) {
                fprintf(file, "5,Gulab Jamun,Deep-fried milk dumplings in sugar syrup,5.00,Desserts\n");
                fprintf(file, "6,Tiramisu,Italian coffee-flavored dessert,6.50,Desserts\n");
            }
            else if (strcmp(filenames[i], FILE_DRINKS) == 0) {
                fprintf(file, "7,Mango Lassi,Traditional Indian yogurt drink,4.99,Drinks\n");
                fprintf(file, "8,Masala Chai,Spiced Indian tea,2.99,Drinks\n");
            }

            fclose(file);
        }
        else {
            fclose(file);  // File already exists, no action needed
        }
    }
}
