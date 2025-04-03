#pragma once

#include "menu.h"

#define MAX_ORDERS 100

// Structure for a single order item
typedef struct {
    char itemID[10];
    char itemName[50];
    float price;
    int quantity;
    char itemCategory[30];  // For time estimation
} Order;

// Order handling functions
int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize);
void applyDiscount(Order orders[], int orderCount, char discountChoice);
void printOrderSummary(Order orders[], int orderCount);

// Time estimation
int calculateDeliveryTime(Order orders[], int orderCount);
int calculatePickupTime(Order orders[], int orderCount);
