#pragma once;
#include <string>
using std::string;

class Item 
{
public:
	Item();
	Item(string type);
	int getItemType();
private:
	string type;
};