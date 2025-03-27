#pragma once

// Handles welcome and user navigation logic
void displayWelcomeMessage();           // Displays welcome screen
int assignRandomTable();                // Assigns a table randomly
int getUserSelection();                 // Gets and validates input (1-4)
void navigateSelection(int selection);  // Routes based on choice
void runCustomerVersion();              // Launches customer side
void runStaffVersion();                 // Launches staff interface
char getYesNoInput(const char* prompt); // Y/N prompt

// Triggers main order process (now moved to order.c or a new file like order_process.c)
void startCustomerOrder(const char* serviceType);
