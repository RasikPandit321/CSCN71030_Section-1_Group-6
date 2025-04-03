#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Global menu storage
MenuItem menu[MAX_MENU_ITEMS];
int menuItemCount = 0;

int LoadMenuFromFile(const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    menuItemCount = 0;
    while (fscanf_s(file, "%d,%49[^,],%249[^,],%f,%19[^\n]",
        &menu[menuItemCount].itemID,
        menu[menuItemCount].itemName, (unsigned)_countof(menu[menuItemCount].itemName),
        menu[menuItemCount].itemDescription, (unsigned)_countof(menu[menuItemCount].itemDescription),
        &menu[menuItemCount].itemPrice,
        menu[menuItemCount].itemCategory, (unsigned)_countof(menu[menuItemCount].itemCategory)) == 5) {
        menuItemCount++;
    }

    fclose(file);
    return 1;
}

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

void DisplayMenu(const char* filename) {
    if (!LoadMenuFromFile(filename)) {
        printf("No items found.\n");
        return;
    }

    if (menuItemCount == 0) {
        printf("No menu items available in this category.\n");
        return;
    }

    printf("\n=== Menu Items from %s ===\n", filename);
    for (int i = 0; i < menuItemCount; i++) {
        printf("ID: %d, Name: %s, Price: $%.2f\nDescription: %s\n\n",
            menu[i].itemID, menu[i].itemName, menu[i].itemPrice, menu[i].itemDescription);
    }
}

int GetMenuItem(char itemCategory[]) {
    const char* filename = GetCategoryFile(itemCategory);
    if (!filename) return 0;
    DisplayMenu(filename);
    return 1;
}

void CreateMenuFileIfNotExists() {
    const char* filenames[] = { FILE_APPETIZERS, FILE_MAIN_COURSE, FILE_DESSERTS, FILE_DRINKS };
    for (int i = 0; i < 4; i++) {
        FILE* file;
        if (fopen_s(&file, filenames[i], "r") != 0) {
            fopen_s(&file, filenames[i], "w");
            if (file != NULL) fclose(file);
        }
        else {
            fclose(file);
        }
    }
}
