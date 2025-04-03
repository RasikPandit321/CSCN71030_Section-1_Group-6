#include <string.h>
#include "menu.h"

int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]) {
    if (menuItemCount >= MAX_MENU_ITEMS) return 0;

    const char* filename = GetCategoryFile(itemCategory);
    if (!filename) return 0;

    int newID = (menuItemCount == 0) ? 1 : menu[menuItemCount - 1].itemID + 1;

    menu[menuItemCount].itemID = newID;
    strcpy_s(menu[menuItemCount].itemName, sizeof(menu[menuItemCount].itemName), itemName);
    strcpy_s(menu[menuItemCount].itemDescription, sizeof(menu[menuItemCount].itemDescription), itemDescription);
    menu[menuItemCount].itemPrice = itemPrice;
    strcpy_s(menu[menuItemCount].itemCategory, sizeof(menu[menuItemCount].itemCategory), itemCategory);

    menuItemCount++;
    return SaveMenuToFile(filename);
}

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

const char* GetCategoryFile(const char* category) {
    if (strcmp(category, "Appetizers") == 0) return FILE_APPETIZERS;
    if (strcmp(category, "Main Course") == 0) return FILE_MAIN_COURSE;
    if (strcmp(category, "Desserts") == 0) return FILE_DESSERTS;
    if (strcmp(category, "Drinks") == 0) return FILE_DRINKS;
    return NULL;
}
