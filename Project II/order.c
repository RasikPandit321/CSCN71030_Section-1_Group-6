#include "order.h"

// Function to add an item to an order list
int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize) {
    if (*orderCount >= MAX_ORDERS) {
        printf("Order limit reached. Cannot add more items.\n");
        return 0;
    }

    // Search for the item in the menu
    for (int i = 0; i < menuSize; i++) {
        if (strcmp(menu[i].itemID, itemID) == 0) {
            // Add the item to the order list
            strcpy(orders[*orderCount].itemID, menu[i].itemID);
            strcpy(orders[*orderCount].itemName, menu[i].itemName);
            orders[*orderCount].price = menu[i].price;
            orders[*orderCount].quantity = quantity;

            (*orderCount)++;  // Increment order count
            printf("Item '%s' added successfully to order.\n", menu[i].itemName);
            return 1;
        }
    }

    printf("Item with ID '%s' not found in menu.\n", itemID);
    return 0;
}

// Example usage (for testing purposes)
int main() {
    // Sample menu items
    MenuItem menu[MAX_ITEMS] = {
        {"101", "Burger", 5.99},
        {"102", "Pizza", 8.49},
        {"103", "Pasta", 6.99},
        {"104", "Salad", 4.99}
    };

    // Order list
    Order orders[MAX_ORDERS];
    int orderCount = 0;

    // Test adding items
    addToOrder(orders, &orderCount, "102", 2, menu, 4); // Adding Pizza
    addToOrder(orders, &orderCount, "105", 1, menu, 4); // Item not in menu

    return 0;
}
