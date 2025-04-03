#pragma once

#include <stdio.h>

#define MAX_MENU_ITEMS 100

// File names for category-specific menu storage
#define FILE_APPETIZERS "appetizers.txt"
#define FILE_MAIN_COURSE "main_course.txt"
#define FILE_DESSERTS "desserts.txt"
#define FILE_DRINKS "drinks.txt"

// Menu item structure
typedef struct {
    int itemID;
    char itemName[50];
    char itemDescription[250];
    float itemPrice;
    char itemCategory[20];
} MenuItem;

// Shared global menu array
extern MenuItem menu[MAX_MENU_ITEMS];
extern int menuItemCount;

// Shared customer and staff operations
int LoadMenuFromFile(const char* filename);
int SaveMenuToFile(const char* filename);
int GetMenuItem(char itemCategory[]);
void DisplayMenu(const char* filename);
void CreateMenuFileIfNotExists();

// Staff-only
int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]);
int RemoveMenuItem(int itemID, const char* filename);
int UpdateMenuItem(int itemID, char itemName[], char itemDescription[], float itemPrice, char itemCategory[], const char* filename);
const char* GetCategoryFile(const char* category);

// Customer-only
void DisplayCustomerMenu();
