#include "pch.h"
#include "CppUnitTest.h"
#include "billing.h"  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BillingModuleTests
{
	TEST_CLASS(BillingModuleTests)
	{
	public:

		// Test Case 1: Generating a Bill with Multiple Items
		TEST_METHOD(Test_GenerateBill)
		{
			OrderItem testItems[] = {
				{"Burger", "Juicy beef burger", 5.99, 2},
				{"Pizza", "Cheesy pizza", 8.99, 1},
				{"Fries", "Crispy fries", 3.49, 1}
			};

			Bill bill = GenerateBill(testItems, 3);
			float expectedSubtotal = (5.99f * 2) + (8.99f * 1) + (3.49f * 1);

			Assert::AreEqual(expectedSubtotal, bill.subtotal, 0.01f, L"Subtotal calculation is incorrect.");

			// Ensure discount is within the expected range (5% - 15%)
			Assert::IsTrue(bill.discount >= 0.05f * expectedSubtotal && bill.discount <= 0.15f * expectedSubtotal, L"Discount is out of expected range.");

			// Validate tax calculation
			float taxableAmount = bill.subtotal - bill.discount;
			float expectedTax = taxableAmount * TAX_RATE;
			Assert::AreEqual(expectedTax, bill.tax, 0.01f, L"Tax calculation is incorrect.");

			// Validate total amount
			float expectedTotal = taxableAmount + expectedTax;
			Assert::AreEqual(expectedTotal, bill.total, 0.01f, L"Total bill calculation is incorrect.");
		}

		// Test Case 2: Applying a Fixed Discount
		TEST_METHOD(Test_ApplyDiscount)
		{
			float subtotal = 50.00f;
			float discount = ApplyDiscount(subtotal, 10.0f);
			Assert::AreEqual(5.00f, discount, 0.01f, L"Fixed discount calculation is incorrect.");
		}

		// Test Case 3: Processing a Successful Payment (Exact Amount Paid)
		TEST_METHOD(Test_ProcessPayment_Success)
		{
			bool result = ProcessPayment("cash", 30.00f, 30.00f);
			Assert::IsTrue(result, L"Payment should be accepted when the exact amount is provided.");
		}

		// Test Case 4: Processing a Payment with Insufficient Amount
		TEST_METHOD(Test_ProcessPayment_Fail)
		{
			bool result = ProcessPayment("card", 20.00f, 25.00f);
			Assert::IsFalse(result, L"Payment should fail if the amount is insufficient.");
		}

		// Test Case 5: Printing and Saving a Receipt
		TEST_METHOD(Test_PrintReceipt)
		{
			OrderItem testItems[] = {
				{"Burger", "Juicy beef burger", 5.99, 1},
				{"Fries", "Crispy fries", 3.49, 1}
			};

			Bill bill = GenerateBill(testItems, 2);
			PrintReceipt(bill);

			// Check if the receipt file was successfully created
			FILE* file = nullptr;
			errno_t err = fopen_s(&file, "C:\\Users\\DELL\\OneDrive - University of Guelph\\Desktop\\Conestoga\\Winter 25\\05 - Project II\\Billing Module\\Billing_Module_Tests\\receipt.txt", "r");

			Assert::AreEqual(0, (int)err, L"Error opening the receipt file.");  // Ensure no error
			Assert::IsNotNull(file, L"Receipt file was not created.");  // Ensure file exists

			if (file) fclose(file);
		}


		// Test Case 6: Handling Invalid Payment Method
		TEST_METHOD(Test_ProcessPayment_InvalidMethod)
		{
			bool result = ProcessPayment("crypto", 40.00f, 40.00f);
			Assert::IsFalse(result, L"Invalid payment methods should be rejected.");
		}
	};
}
