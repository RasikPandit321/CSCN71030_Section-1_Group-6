#define _CRT_SECURE_NO_WARNINGS  // Disable warnings for unsafe functions in Visual Studio

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

    // If file does not exist OR is empty, create and add default items
    if (!file || fgetc(file) == EOF) {
        if (file) fclose(file); // Close empty file if it exists

        file = fopen(MENU_FILE, "w");
        if (!file) {
            printf("Error creating menu file.\n");
            return;
        }

        printf("Writing default menu items to menu.txt...\n");

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


int LoadMenuFromFile() {
    CreateMenuFileIfNotExists(); // Ensure menu file exists before loading
    FILE* file = fopen(MENU_FILE, "r");
    if (!file) {
        printf("Error opening menu file.\n");
        return 0;
    }

    menuItemCount = 0;
    printf("Loading menu items from file...\n");

    while (fscanf(file, "%d,%49[^,],%249[^,],%f,%19[^\n]",
        &menu[menuItemCount].itemID,
        menu[menuItemCount].itemName,
        menu[menuItemCount].itemDescription,
        &menu[menuItemCount].itemPrice,
        menu[menuItemCount].itemCategory) == 5) {
        printf("Loaded: ID=%d, Name=%s, Category=%s\n",
            menu[menuItemCount].itemID,
            menu[menuItemCount].itemName,
            menu[menuItemCount].itemCategory);
        menuItemCount++;
    }

    fclose(file);
    return 1;
}


// Save menu items to file
int SaveMenuToFile() {
    FILE* file = fopen(MENU_FILE, "w");
    if (!file) return 0;

    for (int i = 0; i < menuItemCount; i++) {
        fprintf(file, "%d,%s,%s,%lf,%s\n", menu[i].itemID, menu[i].itemName,
            menu[i].itemDescription, menu[i].itemPrice, menu[i].itemCategory);
    }
    fclose(file);
    return 1;
}

int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]) {
    if (menuItemCount >= MAX_MENU_ITEMS) return 0;

    int newID = (menuItemCount == 0) ? 1 : menu[menuItemCount - 1].itemID + 1;
    menu[menuItemCount].itemID = newID;
    strcpy(menu[menuItemCount].itemName, itemName);
    strcpy(menu[menuItemCount].itemDescription, itemDescription);
    menu[menuItemCount].itemPrice = itemPrice;
    strcpy(menu[menuItemCount].itemCategory, itemCategory);
    menuItemCount++;

    return SaveMenuToFile();
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
            strcpy(menu[i].itemName, itemName);
            strcpy(menu[i].itemDescription, itemDescription);
            menu[i].itemPrice = itemPrice;
            strcpy(menu[i].itemCategory, itemCategory);
            return SaveMenuToFile();
        }
    }
    return 0;
}

// Retrieve menu items by category
int GetMenuItem(char itemCategory[]) {
    LoadMenuFromFile(); // Ensure latest data is loaded
    DisplayMenu();
    return 1;
}

void DisplayMenu() {
    LoadMenuFromFile(); // Ensure latest data is loaded
    printf("\nRestaurant Menu (%d items loaded):\n", menuItemCount);

    for (int i = 0; i < 3; i++) {
        printf("\n%s:\n", categories[i]);
        int found = 0;
        for (int j = 0; j < menuItemCount; j++) {
            if (strcmp(menu[j].itemCategory, categories[i]) == 0) {
                printf("ID: %d, Name: %s, Description: %s, Price: %lf\n",
                    menu[j].itemID, menu[j].itemName,
                    menu[j].itemDescription, menu[j].itemPrice);
                found = 1;
            }
        }
        if (!found) printf("(No items found in this category)\n");
    }
}

// Main function for testing
//int main() {
//    if (!LoadMenuFromFile()) {
//        printf("Error loading menu from file. Ensure the file exists and is formatted correctly.\n");
//        return 1;
//    }
//    printf("\n--- Menu Management System ---\n");
//    DisplayMenu();
//    AddMenuItem("Pizza", "Cheesy and delicious", (float)8.99, "Main Course");
//    UpdateMenuItem(2, "Veg Spring Rolls", "Crispy rolls with vegetables", 3.50, "Appetizers");
//    RemoveMenuItem(1);
//    printf("\nUpdated Menu:\n");
//    DisplayMenu();
//    return 0;
//}