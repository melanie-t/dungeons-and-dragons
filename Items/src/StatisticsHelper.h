#pragma once

#include "Markup.h"

class Statistics
{
private:
	static Statistics* singleton;
	CMarkup xml;
public:
	int getNumMaps();
	int getNumItems();
	void setNumMaps(int num);
	void setNumItems(int num);
	static Statistics* getInstance();

};