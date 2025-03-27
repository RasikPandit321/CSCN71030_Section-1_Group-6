#include "billing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generate a bill with random discount and tax
Bill GenerateBill(OrderItem orderItems[], int itemCount) {
    Bill bill = { 0 };
    bill.itemCount = itemCount;
    bill.subtotal = 0.0;

    for (int i = 0; i < itemCount; i++) {
        bill.items[i] = orderItems[i];
        bill.subtotal += orderItems[i].price * orderItems[i].quantity;
    }

    // Apply random discount between 5% and 15%
    double discountPercentage = (rand() % 11) + 5;
    bill.discount = ApplyDiscount(bill.subtotal, discountPercentage);

    // Apply tax on discounted amount
    double taxable = bill.subtotal - bill.discount;
    bill.tax = taxable * TAX_RATE;
    bill.total = taxable + bill.tax;

    return bill;
}

// Basic percentage discount calculator
double ApplyDiscount(double subtotal, double discountPercentage) {
    return (subtotal * discountPercentage) / 100.0;
}

// Handle payment and check if sufficient
bool ProcessPayment(const char* paymentMethod, double amountPaid, double totalAmount) {
    if (strcmp(paymentMethod, "cash") == 0 || strcmp(paymentMethod, "card") == 0) {
        printf("Payment method: %s\n", paymentMethod);
        if (amountPaid >= totalAmount) {
            printf("Payment successful! Change due: $%.2f\n", amountPaid - totalAmount);
            return true;
        }
        else {
            printf("Insufficient amount! Please pay at least $%.2f\n", totalAmount);
            return false;
        }
    }
    else {
        printf("Invalid payment method! Please select 'cash' or 'card'.\n");
        return false;
    }
}

// Print and save the receipt to file
void PrintReceipt(Bill bill) {
    printf("\n===== Receipt =====\n");
    for (int i = 0; i < bill.itemCount; i++) {
        printf("%s x%d - $%.2f each\n", bill.items[i].name, bill.items[i].quantity, bill.items[i].price);
    }
    printf("\nSubtotal: $%.2f\n", bill.subtotal);
    printf("Discount: $%.2f\n", bill.discount);
    printf("Tax (10%%): $%.2f\n", bill.tax);
    printf("Total: $%.2f\n", bill.total);
    printf("===================\n");

    FILE* file = fopen("receipt.txt", "w");
    if (file != NULL) {
        fprintf(file, "===== Receipt =====\n");
        for (int i = 0; i < bill.itemCount; i++) {
            fprintf(file, "%s x%d - $%.2f each\n", bill.items[i].name, bill.items[i].quantity, bill.items[i].price);
        }
        fprintf(file, "\nSubtotal: $%.2f\n", bill.subtotal);
        fprintf(file, "Discount: $%.2f\n", bill.discount);
        fprintf(file, "Tax (10%%): $%.2f\n", bill.tax);
        fprintf(file, "Total: $%.2f\n", bill.total);
        fprintf(file, "===================\n");
        fclose(file);
        printf("Receipt saved to receipt.txt\n");
    }
    else {
        printf("Error saving receipt to file.\n");
    }
}
