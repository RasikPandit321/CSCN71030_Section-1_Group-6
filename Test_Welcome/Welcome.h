#pragma once
extern bool tables[10];  // So the test can access it

// Function prototype for displaying the welcome message
void displayWelcomeMessage();   // diplays welcome message and menu options
int assignRandomTable();
int getUserSelection();       // gets and validate the user's selection
void navigateSelection(int selection);  // directs the user based on their selection

