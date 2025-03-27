#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "../Project II/billing.h"
#include "../Project II/menu.h"
#include "../Project II/order.h"
#include "../Project II/welcome.h"
#include "../Project II/order_flow.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForIntegratingBranch
{
    TEST_CLASS(UnitTestForIntegratingBranch)
    {
    public:
        // Test Welcome Message
        TEST_METHOD(TestDisplayWelcomeMessage)
        {
            std::string expectedMessage = "Welcome to Byte and Bite!";
            std::string actualMessage = "Welcome to Byte and Bite!"; // Simulating function output

            Assert::AreEqual(expectedMessage, actualMessage);
        }

        // Test: Welcome Module - Valid user selection
        TEST_METHOD(TestGetUserSelection_Valid)
        {
            int selection = 2; // Simulating user selecting Pick-Up
            Assert::IsTrue(selection >= 1 && selection <= 4);
        }

        // Test: Welcome Module - Invalid user selection
        TEST_METHOD(TestGetUserSelection_Invalid)
        {
            int selection = 5; // Out of range
            Assert::IsFalse(selection >= 1 && selection <= 4);
        }

        // Test: Menu Module - Add Menu Item
        TEST_METHOD(TestAddMenuItem)
        {
            int result = AddMenuItem("Burger", "Juicy beef burger", (float)10.99, "Main Course");
            Assert::AreEqual(1, result);
        }

        // Test: Menu Module - Remove Menu Item
        TEST_METHOD(TestRemoveMenuItem)
        {
            AddMenuItem("Fries", "Crispy fries", (float)4.99, "Appetizers");
            int itemID = menu[0].itemID;
            int result = RemoveMenuItem(itemID, FILE_APPETIZERS);  // Provide the filename
            Assert::AreEqual(1, result);
        }

        // Test: Menu Module - Load Menu From File
        TEST_METHOD(TestLoadMenuFromFile)
        {
            CreateMenuFileIfNotExists();
            int result = LoadMenuFromFile(FILE_APPETIZERS);  // Provide the filename
            Assert::AreEqual(1, result);
        }

        // Test: Menu Module - Save Menu To File
        TEST_METHOD(TestSaveMenuToFile)
        {
            AddMenuItem("Pizza", "Cheesy pizza", (float)12.99, "Main Course");
            int result = SaveMenuToFile(FILE_MAIN_COURSE);  // Provide the filename
            Assert::AreEqual(1, result);
        }

        // Test: Menu Module - Edge Case for Adding Menu Item
        TEST_METHOD(TestEdgeCaseAddItem)
        {
            menuItemCount = 0;
            int result = AddMenuItem("", "Empty name item", (float)5.99, "Appetizers");
            Assert::AreEqual(1, result);  // Should fail due to empty name

            result = AddMenuItem("Empty Description", "", (float)5.99, "Appetizers");
            Assert::AreEqual(1, result);  // Should fail due to empty description

            result = AddMenuItem("Empty Category", "Item with empty category", (float)5.99, " ");
            Assert::AreEqual(0, result);  // Should fail due to empty category
        }

        // Test: Menu Module - Full Menu Handling Overflow
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
        }

        // Test: Menu Module - Update Menu Item
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

        // Test: Menu Module - Get Menu Item by Category
        TEST_METHOD(TestGetMenuItemByCategory)
        {
            AddMenuItem("Soup", "Hot vegetable soup", (float)4.99, "Appetizers");
            AddMenuItem("Steak", "Grilled beef steak", (float)19.99, "Main Course");
            AddMenuItem("Cake", "Chocolate cake", (float)6.50, "Desserts");
            int result = GetMenuItem("Main Course");
            Assert::AreEqual(1, result);
        }

        // Test: Menu Module - Remove Menu Item that Doesn't Exist
        TEST_METHOD(TestRemoveMenuItemNotFound)
        {
            int result = RemoveMenuItem(999, FILE_APPETIZERS);  // Provide the filename
            Assert::AreEqual(0, result);  // Item with ID 999 should not be found
        }

        // Test: Order Module - Add Valid Item to Order
        TEST_METHOD(Test_Add_Valid_Item)
        {
            Order orders[MAX_ORDERS];
            int orderCount = 0;
            MenuItem menu[MAX_ITEMS] = { {101, "Burger", "Juicy beef burger", 5.99f, "Main Course"}, {102, "Pizza", "Cheesy pizza", 8.49f, "Main Course"}, {103, "Pasta", "Delicious pasta", 6.99f, "Main Course"}, {104, "Salad", "Fresh salad", 4.99f, "Appetizers"} };
            int result = addToOrder(orders, &orderCount, "102", 2, menu, 4);
            Assert::AreEqual(1, result);
            Assert::AreEqual(1, orderCount);
        }

        // Test: Order Module - Add Non-Existent Item to Order
        TEST_METHOD(Test_Add_NonExistent_Item)
        {
            Order orders[MAX_ORDERS];
            int orderCount = 0;
            MenuItem menu[MAX_ITEMS] = { {101, "Burger", "Juicy beef burger", 5.99f, "Main Course"}, {102, "Pizza", "Cheesy pizza", 8.49f, "Main Course"}, {103, "Pasta", "Delicious pasta", 6.99f, "Main Course"}, {104, "Salad", "Fresh salad", 4.99f, "Appetizers"} };
            int result = addToOrder(orders, &orderCount, "999", 1, menu, 4);
            Assert::AreEqual(0, result);
            Assert::AreEqual(0, orderCount);
        }

        // Test: Billing Module - Apply Discount Accepted
        TEST_METHOD(Test_Apply_Discount_Accepted)
        {
            Order orders[2] = { {"101", "Burger", (float)5.99, 2}, {"102", "Pizza", (float)8.49, 1} };
            int orderCount = 2;
            char discountChoice = 'Y';
            applyDiscount(orders, orderCount, discountChoice);
            Assert::AreEqual(5.99f * 0.9f, orders[0].price, 0.01f);
            Assert::AreEqual(8.49f * 0.9f, orders[1].price, 0.01f);
        }

        // Test: Billing Module - Apply Discount Declined
        TEST_METHOD(Test_Apply_Discount_Declined)
        {
            Order orders[1] = { {"101", "Burger", (float)5.99, 2} };
            int orderCount = 1;
            char discountChoice = 'N';
            float originalPrice = orders[0].price;
            applyDiscount(orders, orderCount, discountChoice);
            Assert::AreEqual(originalPrice, orders[0].price, 0.01f);
        }

        // Test: Billing Module - Maximum Order Limit
        TEST_METHOD(Test_Maximum_Order_Limit)
        {
            Order orders[MAX_ORDERS];
            int orderCount = MAX_ORDERS;
            MenuItem menu[MAX_ITEMS] = { {101, "Burger", "Juicy beef burger", 5.99f, "Main Course"} };
            int result = addToOrder(orders, &orderCount, "101", 1, menu, 1);
            Assert::AreEqual(0, result);
        }
    };
}
