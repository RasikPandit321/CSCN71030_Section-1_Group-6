#include "order.h"
#include <string.h>
#include <stdio.h>

// Add an item to the order
int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize) {
    if (*orderCount >= MAX_ORDERS) {
        printf("Order limit reached. Cannot add more items.\n");
        return 0;
    }

    for (int i = 0; i < menuSize; i++) {
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

// Apply discount (flat 10% off)
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
    int time = 15; // Base delivery time
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].itemCategory, "Appetizers") == 0) time += orders[i].quantity * 3;
        else if (strcmp(orders[i].itemCategory, "Main Course") == 0) time += orders[i].quantity * 7;
        else if (strcmp(orders[i].itemCategory, "Desserts") == 0) time += orders[i].quantity * 2;
        else if (strcmp(orders[i].itemCategory, "Drinks") == 0) time += orders[i].quantity * 1;
    }
    return time;
}

// Calculate pickup time (excluding delivery buffer)
int calculatePickupTime(Order orders[], int orderCount) {
    int time = 0;
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].itemCategory, "Appetizers") == 0) time += orders[i].quantity * 3;
        else if (strcmp(orders[i].itemCategory, "Main Course") == 0) time += orders[i].quantity * 7;
        else if (strcmp(orders[i].itemCategory, "Desserts") == 0) time += orders[i].quantity * 2;
        else if (strcmp(orders[i].itemCategory, "Drinks") == 0) time += orders[i].quantity * 1;
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
