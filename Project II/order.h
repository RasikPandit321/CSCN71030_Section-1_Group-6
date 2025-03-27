#pragma once

#include "menu.h"

#define MAX_ORDERS 100

typedef struct {
    char itemID[10];           // itemID stored as string for consistency
    char itemName[50];
    float price;
    int quantity;
    char itemCategory[30];     // Needed for delivery time estimation
} Order;

// Function declarations
int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize);
int getMenuItemDetails(const MenuItem menu[], int menuSize, const char itemID[], char* itemName, float* price);
void applyDiscount(Order orders[], int orderCount, char discountChoice);
int calculateDeliveryTime(Order orders[], int orderCount);
int calculatePickupTime(Order orders[], int orderCount);
void printOrderSummary(Order orders[], int orderCount);
