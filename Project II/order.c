#include "order.h"
#include <string.h>
#include <stdio.h>

// Function to add an item to an order list
int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize) {
    if (*orderCount >= MAX_ORDERS) {
        printf("Order limit reached. Cannot add more items.\n");
        return 0;
    }

    for (int i = 0; i < menuSize; i++) {
        // Compare integer itemID with formatted string
        char idBuffer[10];
        sprintf_s(idBuffer, sizeof(idBuffer), "%d", menu[i].itemID);

        if (strcmp(idBuffer, itemID) == 0) {
            strcpy_s(orders[*orderCount].itemID, sizeof(orders[*orderCount].itemID), idBuffer);
            strcpy_s(orders[*orderCount].itemName, sizeof(orders[*orderCount].itemName), menu[i].itemName);
            strcpy_s(orders[*orderCount].itemCategory, sizeof(orders[*orderCount].itemCategory), menu[i].itemCategory);
            orders[*orderCount].price = menu[i].itemPrice;
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
        char idBuffer[10];
        sprintf_s(idBuffer, sizeof(idBuffer), "%d", menu[i].itemID);
        if (strcmp(idBuffer, itemID) == 0) {
            strcpy_s(itemName, 50, menu[i].itemName);
            *price = menu[i].itemPrice;
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
            orders[i].price *= 0.9f;
        }
        printf("Discount applied successfully!\n");
    }
    else {
        printf("No discount applied.\n");
    }
}

// Calculate delivery time
int calculateDeliveryTime(Order orders[], int orderCount) {
    int time = 10; // Base time
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].itemCategory, "Drinks") == 0) time += 1;
        else if (strcmp(orders[i].itemCategory, "Appetizers") == 0) time += 3;
        else if (strcmp(orders[i].itemCategory, "Main Course") == 0) time += 5;
        else if (strcmp(orders[i].itemCategory, "Desserts") == 0) time += 2;
    }
    return time;
}

// Calculate pickup time
int calculatePickupTime(Order orders[], int orderCount) {
    int time = 0;
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].itemCategory, "Drinks") == 0) time += 1;
        else if (strcmp(orders[i].itemCategory, "Appetizers") == 0) time += 3;
        else if (strcmp(orders[i].itemCategory, "Main Course") == 0) time += 5;
        else if (strcmp(orders[i].itemCategory, "Desserts") == 0) time += 2;
    }
    return time;
}

// Print order summary
void printOrderSummary(Order orders[], int orderCount) {
    printf("\n===== Order Summary =====\n");
    for (int i = 0; i < orderCount; i++) {
        printf("%s x%d - $%.2f each\n", orders[i].itemName, orders[i].quantity, orders[i].price);
    }
}
