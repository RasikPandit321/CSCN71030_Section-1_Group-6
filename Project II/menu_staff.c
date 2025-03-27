#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"

// Function to determine the file based on category
const char* GetCategoryFile(const char* category) {
    if (strcmp(category, "Appetizers") == 0) return FILE_APPETIZERS;
    if (strcmp(category, "Main Course") == 0) return FILE_MAIN_COURSE;
    if (strcmp(category, "Desserts") == 0) return FILE_DESSERTS;
    if (strcmp(category, "Drinks") == 0) return FILE_DRINKS;
    return NULL;  // Invalid category
}
