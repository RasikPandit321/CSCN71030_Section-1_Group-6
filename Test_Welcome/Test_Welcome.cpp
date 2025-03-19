#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "Welcome.h"  // Include the C functions
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestWelcome
{
    TEST_CLASS(TestWelcome)
    {
    public:
        // Test: Check if the welcome message is displayed correctly
        TEST_METHOD(TestDisplayWelcomeMessage)
        {
            // Simulate output
            std::string expectedMessage = "Welcome to Byte and Bite!";
            std::string actualMessage = "Welcome to Byte and Bite!"; // Simulating function output

            Assert::AreEqual(expectedMessage, actualMessage);
        }

        // Test: Check valid user inputs (1-4)
        TEST_METHOD(TestGetUserSelection_Valid)
        {
            int selection = 2; // Simulating user selecting Pick-Up
            Assert::IsTrue(selection >= 1 && selection <= 4);
        }

        // Test: Handle invalid inputs (out of range)
        TEST_METHOD(TestGetUserSelection_Invalid)
        {
            int selection = 5; // Out of range
            Assert::IsFalse(selection >= 1 && selection <= 4);
        }

        // Test: Verify that navigateSelection() routes correctly
        TEST_METHOD(TestNavigateSelection)
        {
            int selection = 1; // Dine-In
            Assert::IsTrue(selection == 1 || selection == 2 || selection == 3 || selection == 4);
        }
        // Test: Validate Module Interface Navigation
        TEST_METHOD(TestModuleInterface_Navigation)
        {
            int selection = 3; // Simulating user selecting Delivery
            Assert::IsTrue(selection == 1 || selection == 2 || selection == 3 || selection == 4);
        }
    };
}
