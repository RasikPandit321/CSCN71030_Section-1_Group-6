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
        TEST_METHOD(TestAddMenuItem)
        {
            int result = AddMenuItem("Burger", "Juicy beef burger", (float)10.99, "Main Course");
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestRemoveMenuItem)
        {
            AddMenuItem("Fries", "Crispy fries", (float)4.99, "Appetizer");
            int itemID = menu[0].itemID;
            int result = RemoveMenuItem(itemID);
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestLoadMenuFromFile)
        {
            int result = LoadMenuFromFile();
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestSaveMenuToFile)
        {
            AddMenuItem("Pizza", "Cheesy pizza", (float)12.99, "Main Course");
            int result = SaveMenuToFile();
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestEdgeCaseAddItem)
        {
            // Reset menuItemCount before the test
            menuItemCount = 0;

            // Load the menu from the file before each test
            LoadMenuFromFile();
            // Try adding an item with an empty name
            int result = AddMenuItem("", "Empty name item", (float)5.99, "Appetizers");
            Assert::AreEqual(0, result);  // Should fail due to empty name

            // Try adding an item with an empty description
            result = AddMenuItem("Empty Description", "", (float)5.99, "Appetizers");
            Assert::AreEqual(0, result);  // Should fail due to empty description

            // Try adding an item with an empty category
            result = AddMenuItem("Empty Category", "Item with empty category", (float)5.99, "");
            Assert::AreEqual(0, result);  // Should fail due to empty category
        }

        TEST_METHOD(TestFullMenu)
        {
            // Reset menuItemCount before the test
            menuItemCount = 0;

            // Add MAX_MENU_ITEMS number of items to the menu
            for (int i = 0; i < MAX_MENU_ITEMS; i++) {
                char itemName[50];
                sprintf_s(itemName, "Item %d", i + 1);
                int result = AddMenuItem(itemName, "Description", (float)9.99, "Main Course");
                Assert::AreEqual(1, result);  // Should succeed until the limit is reached
            }

            // Verify if we successfully added MAX_MENU_ITEMS items
            Assert::AreEqual(MAX_MENU_ITEMS, menuItemCount);

            // Try adding one more item, which should fail because the menu is full
            int result = AddMenuItem("Overflow Item", "This should not be added", (float)9.99, "Main Course");
            Assert::AreEqual(0, result);  // Should fail due to reaching MAX_MENU_ITEMS limit

            // Verify if the item count is still MAX_MENU_ITEMS after the failed addition
            Assert::AreEqual(MAX_MENU_ITEMS, menuItemCount);
        }

        TEST_METHOD(TestUpdateMenuItem)
        {
            // Add an item to be updated
            AddMenuItem("Pasta", "Delicious pasta", (float)8.99, "Main Course");
            int itemID = menu[0].itemID;  // Get the itemID of the newly added item

            // Update the item's information
            int result = UpdateMenuItem(itemID, "Updated Pasta", "Updated description", (float)10.99, "Main Course");
            Assert::AreEqual(1, result);  // Should succeed

            // Check if the update has been applied
            Assert::AreEqual(0, strcmp(menu[0].itemName, "Updated Pasta"));  // Name should be updated
            Assert::AreEqual(0, strcmp(menu[0].itemDescription, "Updated description"));  // Description should be updated
            Assert::AreEqual(10.99f, menu[0].itemPrice);  // Price should be updated
        }

        TEST_METHOD(TestGetMenuItemByCategory)
        {
            // Add items to different categories
            AddMenuItem("Soup", "Hot vegetable soup", (float)4.99, "Appetizers");
            AddMenuItem("Steak", "Grilled beef steak", (float)19.99, "Main Course");
            AddMenuItem("Cake", "Chocolate cake", (float)6.50, "Desserts");

            // Retrieve and assert the items in the "Main Course" category
            int result = GetMenuItem("Main Course");
            Assert::AreEqual(1, result);  // Should find items in the "Main Course" category
        }

        TEST_METHOD(TestRemoveMenuItemNotFound)
        {
            // Try to remove an item that doesn't exist
            int result = RemoveMenuItem(999);  // Assuming item ID 999 doesn't exist
            Assert::AreEqual(0, result);  // Should fail (return 0)
        }

    };
}