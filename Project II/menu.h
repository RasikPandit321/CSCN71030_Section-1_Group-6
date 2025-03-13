#pragma once
#include <string.h>

/*1. REQ - MENU - 001: This module shall allow the addition of food items with it names, description and price in their respective section.
2. REQ - MENU - 002 : This module shall allow the removal of existing menu items based on a unique name.
3. REQ - MENU - 003 : This module shall allow the modification of menu items and it’s details such as name, description, price and so on.
4. REQ - MENU - 004 : The module shall store food items in a data structure like in a array structure for each section and also ensure that the list is easily accessible for querying, updating, and deleting.
5. REQ - MENU - 005 : This module shall provide functionality to retrieve a list of items for each section when requested by other modules such as Order module.
6. REQ - MENU - 006 : The module should allow searching for food items by their name or category such as drink or soup.
*/
/*Menu Module:
Function: AddMenuItem()
purpose: The purpose of this function is to add new items in a specific section in the menu.
input: itemName(string), itemDescription(string), itemPrice(float), itemCatefory(string)
output: None
return values: integer(1 for success and 0 for the failure)

Function: RemoveMenuItem()
purpose: remove the food items by it’s unique items id.
input: itemID(Int)
output: None
return values: integer(1 for success and 0 for the failure)

Function: UpdateMenuItem()
purpose: updating the food items name, descriptions, or prices of an exiting menu items.
input: itemID(int), itemName(String), itemDescription(string), itemPrice(float).
output: None
return values: integer(1 for success and 0 for the failure)

Function: GetMenuItem()
purpose: it retrieve the whole menu or items from a specific section from the file.
input: Category(string)
output: List of menu items with their name, description, and prices.
return values: integer(1 for success and 0 for the failure)
*/

#define MAX_MENU_ITEMS 90			// maximum amount of food items in the menu

//structure to store the menu items
typedef struct MenuItem {
	int itemID;		//unique id for items
	char itemName[50];    // items name 
	char itemDescription[250];	//items description 
	float itemPrice;    // price for food items
	char itemCategory[50];	//category for food items
}MenuItem;


//Function to add a new menu item
int AddMenuItem(char itemName[], char itemDescription[], float itemPrice, char itemCategory[]);

//Function to remove a menu item
int RemoveMenuItem(int itemID);