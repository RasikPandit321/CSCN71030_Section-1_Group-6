#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "../Project II/menu.h"
}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForWelcomeModule
{
	TEST_CLASS(UnitTestForWelcomeModule)
	{
	public:
        TEST_METHOD(TestAddMenuItem)
        {
                int result = AddMenuItem("Burger", "Juicy beef burger", 10.99, "Main Course");
                Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestRemoveMenuItem)
        {
            AddMenuItem("Fries", "Crispy fries", 4.99, "Appetizer");
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
                AddMenuItem("Pizza", "Cheesy pizza", 12.99, "Main Course");
                int result = SaveMenuToFile();
                Assert::AreEqual(1, result);
        }
    };
}