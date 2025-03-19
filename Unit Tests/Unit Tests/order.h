#pragma once
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {  // Ensure functions are correctly linked when using C++
#endif

    // Maximum Orders and Items
#define MAX_ORDERS 50
#define MAX_ITEMS 90

// Structure to store a single menu item
    typedef struct {
        char itemID[10];
        char itemName[50];
        float price;
    } MenuItem;

    // Structure to store an order
    typedef struct {
        char itemID[10];
        char itemName[50];
        float price;
        int quantity;
    } Order;

    // Function declarations
    int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize);
    int getMenuItemDetails(const MenuItem menu[], int menuSize, const char itemID[], char* itemName, float* price);
    void applyDiscount(Order orders[], int orderCount, char discountChoice);

#ifdef __cplusplus
}  // End extern "C"
#endif
