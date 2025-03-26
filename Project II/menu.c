#define _CRT_SECURE_NO_WARNINGS  // Disable unsafe function warnings in Visual Studio

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

MenuItem menu[MAX_MENU_ITEMS];
int menuItemCount = 0;

// Predefined menu categories
const char* categories[] = { "Appetizers", "Main Course", "Desserts" };

// Function to create menu.txt with default values if it does not exist
void CreateMenuFileIfNotExists() {
    FILE* file = fopen(MENU_FILE, "r");

    if (!file || fgetc(file) == EOF) {  // If file is missing or empty
        if (file) fclose(file);

        file = fopen(MENU_FILE, "w");
        if (!file) {
            printf("Error creating menu file.\n");
            return;
        }

        fprintf(file, "1,Samosa,Crispy fried pastry stuffed with spicy potatoes,2.50,Appetizers\n");
        fprintf(file, "2,Spring Rolls,Vegetable-stuffed crispy rolls,3.00,Appetizers\n");
        fprintf(file, "3,Momo,Nepali dumplings with meat or vegetable filling,5.00,Appetizers\n");
        fprintf(file, "4,Butter Chicken,Creamy tomato-based chicken curry,12.00,Main Course\n");
        fprintf(file, "5,Chow Mein,Stir-fried noodles with vegetables and meat,10.00,Main Course\n");
        fprintf(file, "6,Lasagna,Layered pasta with cheese and tomato sauce,14.00,Main Course\n");
        fprintf(file, "7,Gulab Jamun,Deep-fried milk dumplings in sugar syrup,5.00,Desserts\n");
        fprintf(file, "8,Tiramisu,Italian coffee-flavored dessert,6.50,Desserts\n");

        fclose(file);
    }
    else {
        fclose(file);
    }
}

// Load menu items from file
int LoadMenuFromFile() {
    CreateMenuFileIfNotExists();  // Ensure menu file exists before loading
    FILE* file = fopen(MENU_FILE, "r");
    if (!file) {
        printf("Error opening menu file.\n");
        return 0;
    }

    menuItemCount = 0;
    while (fscanf(file, "%d,%49[^,],%249[^,],%f,%19[^\n]",
        &menu[menuItemCount].itemID,
        menu[menuItemCount].itemName,
        menu[menuItemCount].itemDescription,
        &menu[menuItemCount].itemPrice,
        menu[menuItemCount].itemCategory) == 5) {
        menuItemCount++;
    }

    fclose(file);
    return 1;
}

// Save menu items to file
int SaveMenuToFile() {
    FILE* file = fopen(MENU_FILE, "w");
    if (!file) {
        printf("Error saving menu to file.\n");
        return 0;
    }

    for (int i = 0; i < menuItemCount; i++) {
        fprintf(file, "%d,%s,%s,%.2f,%s\n", menu[i].itemID, menu[i].itemName,
            menu[i].itemDescription, menu[i].itemPrice, menu[i].itemCategory);
    }

    fclose(file);
    return 1;
}

int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]) {
    if (menuItemCount >= MAX_MENU_ITEMS) {
        return 0;  // Return 0 if menu is full
    }

    // Edge case: Check for empty fields
    if (itemName[0] == '\0' || itemDescription[0] == '\0' || itemCategory[0] == '\0') {
        return 0;  // Fail if any field is empty
    }

    int newID = (menuItemCount == 0) ? 1 : menu[menuItemCount - 1].itemID + 1;
    menu[menuItemCount].itemID = newID;

    strcpy_s(menu[menuItemCount].itemName, sizeof(menu[menuItemCount].itemName), itemName);
    strcpy_s(menu[menuItemCount].itemDescription, sizeof(menu[menuItemCount].itemDescription), itemDescription);
    strcpy_s(menu[menuItemCount].itemCategory, sizeof(menu[menuItemCount].itemCategory), itemCategory);

    menu[menuItemCount].itemPrice = itemPrice;
    menuItemCount++;

    return 1;  // Return 1 if item is successfully added
}


// Remove a menu item
int RemoveMenuItem(int itemID) {
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
    return found ? SaveMenuToFile() : 0;
}

// Update a menu item
int UpdateMenuItem(int itemID, char itemName[], char itemDescription[], float itemPrice, char itemCategory[]) {
    for (int i = 0; i < menuItemCount; i++) {
        if (menu[i].itemID == itemID) {
            strcpy_s(menu[i].itemName, sizeof(menu[i].itemName), itemName);
            strcpy_s(menu[i].itemDescription, sizeof(menu[i].itemDescription), itemDescription);
            menu[i].itemPrice = itemPrice;
            strcpy_s(menu[i].itemCategory, sizeof(menu[i].itemCategory), itemCategory);
            return SaveMenuToFile();
        }
    }
    return 0;
}


// Display menu items
void DisplayMenu() {
    if (menuItemCount == 0) {
        printf("No menu items available.\n");
        return;
    }

    printf("\nRestaurant Menu (%d items loaded):\n", menuItemCount);

    for (int i = 0; i < 3; i++) {
        printf("\n%s:\n", categories[i]);
        for (int j = 0; j < menuItemCount; j++) {
            if (strcmp(menu[j].itemCategory, categories[i]) == 0) {
                printf("ID: %d, Name: %s, Description: %s, Price: %.2f\n",
                    menu[j].itemID, menu[j].itemName,
                    menu[j].itemDescription, menu[j].itemPrice);
            }
        }
    }
}

// Retrieve and display menu items by category
int GetMenuItem(char itemCategory[]) {
    int found = 0;

    printf("\nItems in Category: %s\n", itemCategory);

    for (int i = 0; i < menuItemCount; i++) {
        if (strcmp(menu[i].itemCategory, itemCategory) == 0) {
            printf("ID: %d | Name: %s | Price: %.2f | Description: %s\n",
                menu[i].itemID, menu[i].itemName, menu[i].itemPrice, menu[i].itemDescription);
            found = 1;
        }
    }

    if (!found) {
        printf("No items found in this category.\n");
    }

    return found;
}