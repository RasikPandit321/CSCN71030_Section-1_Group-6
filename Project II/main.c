#include <stdio.h>
#include "main.h"
#include "menu.h"

int main() {
    // Load menu from file
    if (!LoadMenuFromFile()) {
        printf("Error loading menu from file.\n");
        return 1;
    }

    // Display menu
    printf("\n--- Restaurant Menu ---\n");
    DisplayMenu();

    // Add a test menu item
    printf("\nAdding a new menu item...\n");
    AddMenuItem("Test Dish", "A sample test dish", 9.99, "Main Course");

    // Display updated menu
    printf("\n--- Updated Menu ---\n");
    DisplayMenu();

    return 0;
}
