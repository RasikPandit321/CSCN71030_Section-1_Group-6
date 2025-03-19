#include <stdio.h>
#include"Welcome.h"

int main()
{
    printf("Hello\n");

        int userChoice;

        // Display the welcome screen
        displayWelcomeMessage();

        // Loop until the user chooses to exit
        while (1) 
        {
            userChoice = getUserSelection();
            if (userChoice == 4)
            {
                navigateSelection(userChoice);
                break; // Exit the loop
            }
            navigateSelection(userChoice);
        }

        return 0;
 }
