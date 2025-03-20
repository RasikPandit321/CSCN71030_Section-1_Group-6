#include <stdio.h>
#include "main.h"
#include "menu.h"

int main() {
    /*printf("Hello!!!\n");
    return 0;

	DisplayMenu();

    return 0;*/

    if (!LoadMenuFromFile()) {
        printf("Error loading menu from file. Ensure the file exists and is formatted correctly.\n");
        return 1;
    }
    printf("\n--- Menu Management System ---\n");
    DisplayMenu();
    AddMenuItem("Pizza", "Cheesy and delicious", (float)8.99, "Main Course");
    UpdateMenuItem(2, "Veg Spring Rolls", "Crispy rolls with vegetables", 3.50, "Appetizers");
    RemoveMenuItem(1);
    printf("\nUpdated Menu:\n");
    DisplayMenu();
    return 0;
    
}
