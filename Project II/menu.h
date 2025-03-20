#pragma once

#include <stdio.h>

#define MAX_MENU_ITEMS 100   // Maximum number of menu items
#define MENU_FILE "menu.txt" // File to store menu items

// Structure to store menu items
typedef struct {
    int itemID;                    // Unique ID for the item
    char itemName[50];              // Name of the item
    char itemDescription[250];      // Description of the item
    float itemPrice;                // Price of the item
    char itemCategory[20];          // Category of the item (Appetizers, Main Course, Desserts)
} MenuItem;

// Global variables
extern MenuItem menu[MAX_MENU_ITEMS];
extern int menuItemCount;

// Function declarations
int LoadMenuFromFile();
int SaveMenuToFile();
int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]);
int RemoveMenuItem(int itemID);
int UpdateMenuItem(int itemID, char itemName[], char itemDescription[], float itemPrice, char itemCategory[]);
int GetMenuItem(char itemCategory[]);
void DisplayMenu();
//void PreloadMenuItems();