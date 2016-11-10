#include "Item.h"

Item::Item()
{
	type = "armor";
}

Item::Item(string name)
{
	type = name;
}

int Item::getItemType() 
{
	if (type.compare("armor") == 0)
		return 1;
	else if (type.compare("belt") == 0)
		return 2;
	else if (type.compare("helmet") == 0)
		return 3;
	else if (type.compare("ring") == 0)
		return 4;
	else if (type.compare("shield") == 0)
		return 5;
	else if (type.compare("boots") == 0)
		return 6;
	else if (type.compare("weapon") == 0)
		return 7;
	else
		return 0;
}
