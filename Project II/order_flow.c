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

    do {
        DisplayCustomerMenu();

        char inputBuffer[20];
        printf("Enter your choice: ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = 0;

        char* endptr;
        menuChoice = strtol(inputBuffer, &endptr, 10);
        if (endptr == inputBuffer || *endptr != '\0' || menuChoice < 1 || menuChoice > 3) {
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
            char category[20];
            printf("Enter category to search (Appetizers, Main Course, Desserts, Drinks): ");
            fgets(category, sizeof(category), stdin);
            category[strcspn(category, "\n")] = 0;
            if (!GetMenuItem(category)) {
                printf("No items found in this category.\n");
            }
            break;
        }
        }
    } while (menuChoice != 3);

    int totalItems = 0;
    const char* files[] = { FILE_APPETIZERS, FILE_MAIN_COURSE, FILE_DESSERTS, FILE_DRINKS };
    for (int i = 0; i < 4; i++) {
        LoadMenuFromFile(files[i]);
        for (int j = 0; j < menuItemCount; j++) {
            allItems[totalItems++] = menu[j];
        }
    }

    char more;
    do {
        char buffer[20];

        printf("Enter Item ID to add: ");
        fgets(itemID, sizeof(itemID), stdin);
        itemID[strcspn(itemID, "\n")] = 0;

        printf("Enter Quantity: ");
        fgets(buffer, sizeof(buffer), stdin);
        quantity = atoi(buffer);

        if (quantity <= 0) {
            printf("Invalid quantity.\n");
        }
        else {
            addToOrder(orders, &orderCount, itemID, quantity, allItems, totalItems);
        }

        more = getYesNoInput("Add more items?");
    } while (more == 'Y');

    srand((unsigned)time(NULL));
    int luckyDiscount = rand() % 2;
    if (luckyDiscount == 1) {
        printf("Congratulations, you qualify for a discount!\n");
        applyDiscount(orders, orderCount, 'Y');
    }
    else {
        printf("Sorry, no discount this time.\n");
        applyDiscount(orders, orderCount, 'N');
    }

    printOrderSummary(orders, orderCount);

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

    char method[10];
    bool validMethod = false;
    while (!validMethod) {
        printf("Enter payment method (cash/card): ");
        fgets(method, sizeof(method), stdin);
        method[strcspn(method, "\n")] = 0;

        if (strcmp(method, "cash") == 0 || strcmp(method, "card") == 0) {
            validMethod = true;
        }
        else {
            printf("Invalid payment method! Please select 'cash' or 'card'.\n");
        }
    }

    char amountInput[20];
    bool validAmount = false;
    double amount = 0.0;
    while (!validAmount) {
        printf("Enter amount paid: ");
        fgets(amountInput, sizeof(amountInput), stdin);
        amountInput[strcspn(amountInput, "\n")] = 0;
        char* endptr;
        amount = strtod(amountInput, &endptr);
        if (endptr == amountInput || *endptr != '\0') {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }
        if (amount < finalBill.total) {
            printf("Insufficient amount! Please pay at least $%.2f\n", finalBill.total);
            continue;
        }
        validAmount = true;
    }

    ProcessPayment(method, amount, finalBill.total);

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
