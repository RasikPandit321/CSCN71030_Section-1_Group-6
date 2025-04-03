#pragma once

#include <stdbool.h>

#define TAX_RATE 0.10
#define MAX_ITEMS 50

// Struct for each item in the bill
typedef struct {
    char name[50];
    char description[100];
    double price;
    int quantity;
} OrderItem;

// Struct for final bill
typedef struct {
    OrderItem items[MAX_ITEMS];
    int itemCount;
    double subtotal;
    double discount;
    double tax;
    double total;
} Bill;

// Core billing functions
Bill GenerateBill(OrderItem orderItems[], int itemCount);
double ApplyDiscount(double subtotal, double discountPercentage);
bool ProcessPayment(const char* paymentMethod, double amountPaid, double totalAmount);
void PrintReceipt(Bill bill);
