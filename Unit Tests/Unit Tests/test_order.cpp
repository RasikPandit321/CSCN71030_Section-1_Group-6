#include "pch.h"
#include "CppUnitTest.h"
#include "order.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OrderModuleTests
{
    TEST_CLASS(OrderTests)
    {
    public:

        TEST_METHOD(Test_Add_Valid_Item) // Test Case 1
        {
            Order orders[MAX_ORDERS];
            int orderCount = 0;
            MenuItem menu[MAX_ITEMS] = {
                {"101", "Burger", (float)5.99},
                {"102", "Pizza", (float)8.49},
                {"103", "Pasta", (float)6.99},
                {"104", "Salad", (float)4.99}
            };

            int result = addToOrder(orders, &orderCount, "102", 2, menu, 4);
            Assert::AreEqual(1, result);
            Assert::AreEqual(2, orderCount);
        }

        TEST_METHOD(Test_Add_NonExistent_Item) // Test Case 2
        {
            Order orders[MAX_ORDERS];
            int orderCount = 0;
            MenuItem menu[MAX_ITEMS] = {
                {"101", "Burger", (float)5.99},
                {"102", "Pizza", (float)8.49},
                {"103", "Pasta", (float)6.99},
                {"104", "Salad", (float)4.99}
            };

            int result = addToOrder(orders, &orderCount, "999", 1, menu, 4);
            Assert::AreEqual(0, result);
            Assert::AreEqual(1, orderCount);
        }

        TEST_METHOD(Test_Add_Item_Zero_Quantity) // Test Case 3
        {
            Order orders[MAX_ORDERS];
            int orderCount = 0;
            MenuItem menu[MAX_ITEMS] = {
                {"101", "Burger", (float)5.99}
            };

            int result = addToOrder(orders, &orderCount, "101", 0, menu, 1);
            Assert::AreEqual(0, result);
            Assert::AreEqual(0, orderCount);
        }

        TEST_METHOD(Test_Get_Item_Details) // Test Case 4
        {
            MenuItem menu[MAX_ITEMS] = {
                {"101", "Burger", (float)5.99},
                {"102", "Pizza", (float)8.49},
                {"103", "Pasta", (float)6.99},
                {"104", "Salad", (float)4.99}
            };

            char itemName[50];
            float price;
            int found = getMenuItemDetails(menu, 4, "103", itemName, &price);

            Assert::AreEqual(1, found); // Ensure item was found
            Assert::AreEqual(std::string("Pasta"), std::string(itemName)); // Convert both to std::string
            Assert::AreEqual(6.99f, price, 0.01f); // Use a tolerance to prevent floating-point precision errors
        }

        TEST_METHOD(Test_Get_NonExistent_Item_Details) // Test Case 5
        {
            MenuItem menu[MAX_ITEMS] = {
                {"101", "Burger", (float)5.99},
                {"102", "Pizza", (float)8.49}
            };

            char itemName[50];
            float price;
            int found = getMenuItemDetails(menu, 2, "999", itemName, &price);

            Assert::AreEqual(0, found);
        }

        TEST_METHOD(Test_Apply_Discount_Accepted) // Test Case 6
        {
            Order orders[2] = {
                {"101", "Burger", (float)5.99, 2},
                {"102", "Pizza", (float)8.49, 1}
            };
            int orderCount = 2;
            char discountChoice = 'Y';

            applyDiscount(orders, orderCount, discountChoice);

            Assert::AreEqual(5.99f * 0.9f, orders[0].price, 0.01f); // Use tolerance for float
            Assert::AreEqual(8.49f * 0.9f, orders[1].price, 0.01f);
        }

        TEST_METHOD(Test_Apply_Discount_Declined) // Test Case 7
        {
            Order orders[1] = {
                {"101", "Burger", (float)5.99, 2}
            };
            int orderCount = 1;
            char discountChoice = 'N';

            float originalPrice = orders[0].price;
            applyDiscount(orders, orderCount, discountChoice);

            Assert::AreEqual(originalPrice, orders[0].price, 0.01f); // Use tolerance for float
        }

        TEST_METHOD(Test_Maximum_Order_Limit) // Test Case 8
        {
            Order orders[MAX_ORDERS];
            int orderCount = MAX_ORDERS;
            MenuItem menu[MAX_ITEMS] = {
                {"101", "Burger", (float)5.99}
            };

            int result = addToOrder(orders, &orderCount, "101", 1, menu, 1);
            Assert::AreEqual(0, result);
        }
    };
}
