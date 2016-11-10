#include "ItemPanel.h"
#include "Item.h"
#include "Chest.h"

int main() {
	ItemPanel::createInventories();
	Item i1("shield");
	Item i2("weapon");
	Item i3("boots");
	Item i4("helmet");
	Item i5("ring");
	Item i6("belt");
	Item i7("armor");
	Chest::displayChest(i1);
	Chest::displayChest(i2);
	Chest::displayChest(i3);
	Chest::displayChest(i4);
	Chest::displayChest(i5);
	Chest::displayChest(i6);
	Chest::displayChest(i7);
	return 0;
}