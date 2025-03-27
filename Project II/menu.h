#pragma once

#include <stdio.h>

#define MAX_MENU_ITEMS 100   // Maximum number of menu items

// Separate files for each category
#define FILE_APPETIZERS "appetizers.txt"
#define FILE_MAIN_COURSE "main_course.txt"
#define FILE_DESSERTS "desserts.txt"
#define FILE_DRINKS "drinks.txt"

// Structure to store menu items
typedef struct {
    int itemID;                    // Unique ID for the item
    char itemName[50];              // Name of the item
    char itemDescription[250];      // Description of the item
    float itemPrice;                // Price of the item
    char itemCategory[20];          // Category of the item (Appetizers, Main Course, Desserts, Drinks)
} MenuItem;

// Global variables
extern MenuItem menu[MAX_MENU_ITEMS];
extern int menuItemCount;

// Function declarations for customer menu operations
int LoadMenuFromFile(const char* filename);
int SaveMenuToFile(const char* filename);
int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]);
int RemoveMenuItem(int itemID, const char* filename);
int UpdateMenuItem(int itemID, char itemName[], char itemDescription[], float itemPrice, char itemCategory[], const char* filename);
void DisplayMenu(const char* filename);
int GetMenuItem(char itemCategory[]);
void CreateMenuFileIfNotExists();

// Function declarations for staff-specific menu operations
const char* GetCategoryFile(const char* category);