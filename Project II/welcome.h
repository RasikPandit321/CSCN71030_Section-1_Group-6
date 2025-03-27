#pragma once

#include "order.h" 

// Function prototypes for welcome and navigation logic
void displayWelcomeMessage();  // Displays welcome message and menu options
int assignRandomTable();       // Assigns a table randomly for dine-in
int getUserSelection();        // Gets and validates the user's selection
void navigateSelection(int selection);  // Directs the user based on selection
void runCustomerVersion();     // Entry point for customer mode
void runStaffVersion();        // Entry point for staff mode
void DisplayCustomerMenu();    // Displays menu browsing options
char getYesNoInput(const char* prompt);  // Prompts user with Y/N and validates
void openMenuModule(const char* serviceType); // Main menu/order logic
int calculateDeliveryTime(Order* orders, int orderCount); // Delivery time estimate
