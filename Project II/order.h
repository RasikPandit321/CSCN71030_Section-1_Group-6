#pragma once
#include <stdio.h>
#include <string.h>

// Maximum Orders and Items
#define MAX_ORDERS 50
#define MAX_ITEMS 10

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

// Function to add an item to an order
int addToOrder(Order orders[], int* orderCount, const char itemID[], int quantity, const MenuItem menu[], int menuSize);

