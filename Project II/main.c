#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Core modules
#include "menu.h"
#include "welcome.h"
#include "order.h"
#include "billing.h"

int main(int argc, char* argv[]) {
    // Seed the random number generator (for discounts, random table assignment, etc.)
    srand((unsigned int)time(NULL));

    // Check arguments to decide which mode to run
    if (argc == 1) {
        // No arguments: Run as customer
        runCustomerVersion();
    }
    else if (argc == 2 && strcmp(argv[1], "1") == 0) {
        // Argument "1": Run as staff
        runStaffVersion();
    }
    else {
        // Invalid usage
        printf("Invalid argument!\n");
        printf("Usage:\n");
        printf("  ./restaurant         -> Run as Customer\n");
        printf("  ./restaurant 1       -> Run as Staff\n");
        return 1;
    }

    return 0;
}
