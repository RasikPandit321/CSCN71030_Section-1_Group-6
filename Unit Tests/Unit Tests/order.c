

#include "order.h"

// Function to add an item to an order list
int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize) {
    if (*orderCount >= MAX_ORDERS) {
        printf("Order limit reached. Cannot add more items.\n");
        return 0;
    }
    if (quantity <= 0) { 
        printf("Invalid quantity. Please enter a value greater than zero.\n");
        return 0;
    }

    for (int i = 0; i < menuSize; i++) {
        if (strcmp(menu[i].itemID, itemID) == 0) {
            // Using strcpy_s for safer string copying
            strcpy_s(orders[*orderCount].itemID, sizeof(orders[*orderCount].itemID), menu[i].itemID);
            strcpy_s(orders[*orderCount].itemName, sizeof(orders[*orderCount].itemName), menu[i].itemName);
            orders[*orderCount].price = menu[i].price;
            orders[*orderCount].quantity = quantity;

            (*orderCount)++;
            printf("Item '%s' added successfully to order.\n", menu[i].itemName);
            return 1;
        }
    }

    printf("Item with ID '%s' not found in menu.\n", itemID);
    return 0;
}

// Function to retrieve menu item details based on item ID
int getMenuItemDetails(const MenuItem menu[], int menuSize, const char itemID[], char* itemName, float* price) {
    for (int i = 0; i < menuSize; i++) {
        if (strcmp(menu[i].itemID, itemID) == 0) {
            // Using strcpy_s for safer string copying
            strcpy_s(itemName, 50, menu[i].itemName);
            *price = menu[i].price;
            return 1;
        }
    }
    return 0;
}

// Function to apply a discount before sending to Billing Module
void applyDiscount(Order orders[], int orderCount, char discountChoice) {
    if (discountChoice == 'Y' || discountChoice == 'y') {
        printf("Applying discount to the order...\n");
        for (int i = 0; i < orderCount; i++) {
            orders[i].price *= (float)0.9;
        }
        printf("Discount applied successfully!\n");
    }
    else {
        printf("No discount applied.\n");
    }
}