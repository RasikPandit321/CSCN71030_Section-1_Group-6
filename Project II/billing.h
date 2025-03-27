#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    // Constants
#define TAX_RATE 0.10
#define MAX_ITEMS 50

// Structures
    typedef struct {
        char name[50];
        char description[100];
        double price;
        int quantity;
    } OrderItem;

    typedef struct {
        OrderItem items[MAX_ITEMS];
        int itemCount;
        double subtotal;
        double discount;
        double tax;
        double total;
    } Bill;

    // Function prototypes
    Bill GenerateBill(OrderItem orderItems[], int itemCount);
    double ApplyDiscount(double subtotal, double discountPercentage);
    bool ProcessPayment(const char* paymentMethod, double amountPaid, double totalAmount);
    void PrintReceipt(Bill bill);

#ifdef __cplusplus
}
#endif