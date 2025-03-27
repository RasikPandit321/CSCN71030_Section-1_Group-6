#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "menu.h"
#include "welcome.h"
#include "billing.h"
#include "order.h"

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL)); // Seed random

    if (argc == 1) {
        // No arguments: Customer Version
        runCustomerVersion();
    }
    else if (argc == 2 && strcmp(argv[1], "1") == 0) {
        // Argument "1": Staff Version
        runStaffVersion();
    }
    else {
        printf("Invalid argument!\nUsage:\n  No argument -> Customer version\n  1 -> Staff version\n");
        return 1;
    }

    return 0;
}