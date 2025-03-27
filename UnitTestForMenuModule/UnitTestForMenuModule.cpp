#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "..//Project II/menu.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForMenuModule
{
    TEST_CLASS(UnitTestForMenuModule)
    {
    public:

        // Test Add Menu Item
        TEST_METHOD(TestAddMenuItem)
        {
            int result = AddMenuItem("Burger", "Juicy beef burger", (float)10.99, "Main Course");
            Assert::AreEqual(1, result);
        }

        // Test Remove Menu Item
        TEST_METHOD(TestRemoveMenuItem)
        {
            AddMenuItem("Fries", "Crispy fries", (float)4.99, "Appetizers");
            int itemID = menu[0].itemID;
            int result = RemoveMenuItem(itemID, FILE_APPETIZERS);  // Provide the filename
            Assert::AreEqual(1, result);
        }

        // Test Load Menu From File
        TEST_METHOD(TestLoadMenuFromFile)
        {
            // Ensure the menu file exists with default items
            CreateMenuFileIfNotExists();

            int result = LoadMenuFromFile(FILE_APPETIZERS);  // Provide the filename
            Assert::AreEqual(1, result);
        }

        // Test Save Menu To File
        TEST_METHOD(TestSaveMenuToFile)
        {
            AddMenuItem("Pizza", "Cheesy pizza", (float)12.99, "Main Course");
            int result = SaveMenuToFile(FILE_MAIN_COURSE);  // Provide the filename
            Assert::AreEqual(1, result);
        }

        // Test Edge Case for Adding Menu Item
        TEST_METHOD(TestEdgeCaseAddItem)
        {
            menuItemCount = 0;

            int result = AddMenuItem("", "Empty name item", (float)5.99, "Appetizers");
            Assert::AreEqual(0, result);  // Should fail due to empty name

            result = AddMenuItem("Empty Description", "", (float)5.99, "Appetizers");
            Assert::AreEqual(0, result);  // Should fail due to empty description

            result = AddMenuItem("Empty Category", "Item with empty category", (float)5.99, "");
            Assert::AreEqual(0, result);  // Should fail due to empty category
        }

        // Test Full Menu and Handling Overflow
        TEST_METHOD(TestFullMenu)
        {
            menuItemCount = 0;
            for (int i = 0; i < MAX_MENU_ITEMS; i++) {
                char itemName[50];
                sprintf_s(itemName, "Item %d", i + 1);
                int result = AddMenuItem(itemName, "Description", (float)9.99, "Main Course");
                Assert::AreEqual(1, result);
            }

            Assert::AreEqual(MAX_MENU_ITEMS, menuItemCount);

            int result = AddMenuItem("Overflow Item", "This should not be added", (float)9.99, "Main Course");
            Assert::AreEqual(0, result);  // Should fail as the menu is full

            Assert::AreEqual(MAX_MENU_ITEMS, menuItemCount);
        }

        // Test Updating Menu Item
        TEST_METHOD(TestUpdateMenuItem)
        {
            AddMenuItem("Pasta", "Delicious pasta", (float)8.99, "Main Course");
            int itemID = menu[0].itemID;

            int result = UpdateMenuItem(itemID, "Updated Pasta", "Updated description", (float)10.99, "Main Course", FILE_MAIN_COURSE);
            Assert::AreEqual(1, result);

            Assert::AreEqual(0, strcmp(menu[0].itemName, "Updated Pasta"));
            Assert::AreEqual(0, strcmp(menu[0].itemDescription, "Updated description"));
            Assert::AreEqual(10.99f, menu[0].itemPrice);
        }

        // Test Get Menu Item by Category
        TEST_METHOD(TestGetMenuItemByCategory)
        {
            AddMenuItem("Soup", "Hot vegetable soup", (float)4.99, "Appetizers");
            AddMenuItem("Steak", "Grilled beef steak", (float)19.99, "Main Course");
            AddMenuItem("Cake", "Chocolate cake", (float)6.50, "Desserts");

            int result = GetMenuItem("Main Course");
            Assert::AreEqual(1, result);
        }

        // Test Remove Menu Item that Doesn't Exist
        TEST_METHOD(TestRemoveMenuItemNotFound)
        {
            int result = RemoveMenuItem(999, FILE_APPETIZERS);  // Provide the filename
            Assert::AreEqual(0, result);  // Item with ID 999 should not be found
        }
    };
}
