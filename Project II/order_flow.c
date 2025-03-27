#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#include "menu.h"
#include "order.h"
#include "billing.h"
#include "welcome.h"
#include "order_flow.h"

// Trim leading/trailing whitespace
void trimWhitespace(char* str) {
    char* start = str;
    while (isspace((unsigned char)*start)) start++;

    if (*start == 0) {
        str[0] = '\0';
        return;
    }

    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';
    memmove(str, start, strlen(start) + 1);
}

void flushInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void startCustomerOrder(const char* serviceType) {
    CreateMenuFileIfNotExists();

    Order* orders = malloc(sizeof(Order) * MAX_ORDERS);
    MenuItem* allItems = malloc(sizeof(MenuItem) * MAX_MENU_ITEMS);
    OrderItem* finalItems = malloc(sizeof(OrderItem) * MAX_ITEMS);

    if (!orders || !allItems || !finalItems) {
        printf("Memory allocation failed.\n");
        free(orders); free(allItems); free(finalItems);
        return;
    }

    int orderCount = 0, quantity;
    char itemID[10];
    int menuChoice;

    // Menu browsing
    do {
        DisplayCustomerMenu();
        char inputBuffer[20];
        printf("Enter your choice: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = 0;

        if (sscanf(inputBuffer, "%d", &menuChoice) != 1 || menuChoice < 1 || menuChoice > 3) {
            printf("Invalid input! Please enter a number between 1 and 3.\n");
            continue;
        }

        switch (menuChoice) {
        case 1:
            DisplayMenu(FILE_APPETIZERS);
            DisplayMenu(FILE_MAIN_COURSE);
            DisplayMenu(FILE_DRINKS);
            DisplayMenu(FILE_DESSERTS);
            break;
        case 2: {
            char category[30];
            printf("Enter category to search (Appetizers, Main Course, Desserts, Drinks): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;
            trimWhitespace(category);
            if (!GetMenuItem(category)) {
                printf("No items found in this category.\n");
            }
            break;
        }
        }
    } while (menuChoice != 3);

    // Load menu items
    int totalItems = 0;
    const char* files[] = { FILE_APPETIZERS, FILE_MAIN_COURSE, FILE_DESSERTS, FILE_DRINKS };
    for (int i = 0; i < 4; i++) {
        LoadMenuFromFile(files[i]);
        for (int j = 0; j < menuItemCount; j++) {
            allItems[totalItems++] = menu[j];
        }
    }

    // Ordering
    char more;
    do {
        // Flush before prompting for new input
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF); // clear buffer after Y/N

        printf("Enter Item ID to add: ");
        fgets(itemID, sizeof(itemID), stdin);
        itemID[strcspn(itemID, "\n")] = 0;

        if (strlen(itemID) == 0) {
            printf("Invalid Item ID.\n");
            continue;
        }

        char quantityBuffer[10];
        printf("Enter Quantity: ");
        fgets(quantityBuffer, sizeof(quantityBuffer), stdin);

        if (sscanf_s(quantityBuffer, "%d", &quantity) != 1 || quantity <= 0) {
            printf("Invalid quantity.\n");
        }
        else {
            addToOrder(orders, &orderCount, itemID, quantity, allItems, totalItems);
        }

        more = getYesNoInput("Add more items?");
    } while (more == 'Y');


    // Discount
    srand((unsigned)time(NULL));
    int luckyDiscount = rand() % 2;
    applyDiscount(orders, orderCount, luckyDiscount ? 'Y' : 'N');
    printOrderSummary(orders, orderCount);

    // Prepare bill
    for (int i = 0; i < orderCount; i++) {
        strcpy_s(finalItems[i].name, sizeof(finalItems[i].name), orders[i].itemName);
        strcpy_s(finalItems[i].description, sizeof(finalItems[i].description), "");
        finalItems[i].price = orders[i].price;
        finalItems[i].quantity = orders[i].quantity;
    }

    Bill finalBill = GenerateBill(finalItems, orderCount);

    if (strcmp(serviceType, "Delivery") == 0) {
        printf("\nDelivery Charge: $7.50 added.\n");
        finalBill.subtotal += 7.50;
        finalBill.tax = finalBill.subtotal * TAX_RATE;
        finalBill.total = finalBill.subtotal - finalBill.discount + finalBill.tax;

        int deliveryTime = calculateDeliveryTime(orders, orderCount);
        printf("Estimated Delivery Time: %d minutes\n", deliveryTime);
    }

    PrintReceipt(finalBill);

    // Payment Method
    char method[20];
    bool validMethod = false;
    while (!validMethod) {
        printf("Enter payment method (cash/card): ");
        fgets(method, sizeof(method), stdin);
        method[strcspn(method, "\n")] = 0;
        trimWhitespace(method);

        if (strcmp(method, "cash") == 0 || strcmp(method, "card") == 0) {
            validMethod = true;
        }
        else {
            printf("Invalid payment method! Please select 'cash' or 'card'.\n");
        }
    }

    // Payment Amount
    char amountInput[20];
    bool validAmount = false;
    double amount = 0.0;
    while (!validAmount) {
        printf("Enter amount paid: ");
        fgets(amountInput, sizeof(amountInput), stdin);
        amountInput[strcspn(amountInput, "\n")] = 0;

        char* endptr;
        amount = strtod(amountInput, &endptr);
        if (endptr == amountInput || *endptr != '\0' || amount < finalBill.total) {
            printf("Invalid or insufficient amount! Please pay at least $%.2f\n", finalBill.total);
            continue;
        }
        validAmount = true;
    }

    ProcessPayment(method, amount, finalBill.total);

    // Cleanup
    free(orders);
    free(allItems);
    free(finalItems);

    printf("\nThank you for dining with us at Byte and Bite!\n");

    char newOrderChoice = getYesNoInput("Would you like to place another order?");
    if (newOrderChoice == 'Y') {
        printf("\nRedirecting to main menu...\n");
        runCustomerVersion();
    }
    else {
        printf("\nThank you for visiting Byte and Bite! Come again soon!\n");
        exit(0);
    }
}
