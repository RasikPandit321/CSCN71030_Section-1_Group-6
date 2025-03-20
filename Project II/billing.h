#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define constants
#define TAX_RATE 0.10  // 10% tax rate
#define MAX_ITEMS 50   // Maximum number of items in an order

// Structure to store an order item
typedef struct {
    char name[50];
    char description[100];
    float price;
    int quantity;
} OrderItem;

// Structure to store the final bill details
typedef struct {
    OrderItem items[MAX_ITEMS];
    int itemCount;
    float subtotal;
    float discount;
    float tax;
    float total;
} Bill;

// Function prototypes
Bill GenerateBill(OrderItem orderItems[], int itemCount);
float ApplyDiscount(float subtotal, float discountPercentage);
bool ProcessPayment(const char* paymentMethod, float amountPaid, float totalAmount);
void PrintReceipt(Bill bill);


