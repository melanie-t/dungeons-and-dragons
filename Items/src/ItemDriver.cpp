//! @file 
//! @brief Driver for testing Item class.

#include <iostream>
#include "Item.h"
#include "ItemContainer.h"
using namespace std;


//! main function
//! @brief This method will test if validateItem() function in the Item class returns false for an invalid Item 
//! and true for a valid item.

int main()
{
	//!@test test case for invalid item: Item of type Ring
	//! with 1 Dexterity Enhancement with value +5
	//! This is illegal according to d20 rules.
	cout << "I will create an Item of Type Ring with 1 Enhancement of type Dexterity with value +5" << endl;
	cout << "This is an illegal according to the d20 rules. validateItem should return false." << endl;
	
	vector<Enhancement> invalidEnhancements; //= new vector<Enhancement>();
	invalidEnhancements.push_back(Enhancement("Dexterity", 5));
	Item* invalidItem = new Item("Ring", invalidEnhancements);

	cout << "Item created." << endl;
	cout << "Result of running validateItem(): ";

	if (invalidItem->validateItem())
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
	}

	cout << "------------------" << endl;
	//!@test test case for invalid item: Item of type Ring
	//! with 1 Strength Enhancement with value +5
	//! This should be accepted according to d20 rules.
	cout << "I will create an Item of Type Ring with 1 Enhancement of type Strength with value +5" << endl;
	cout << "This is an legal according to the d20 rules. validateItem should return True." << endl;

	vector<Enhancement> validEnhancements; //= new vector<Enhancement>();
	validEnhancements.push_back(Enhancement("Strength", 5));
	Item* validItem = new Item("Ring", validEnhancements);

	cout << "Item created." << endl;
	cout << "Result of running validateItem(): ";

	if (validItem->validateItem())
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
	}

	// So that you may see the results without the console closing.
	system("pause");

}