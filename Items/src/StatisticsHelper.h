#pragma once

#include "Markup.h"

class Statistics
{
private:
	CMarkup xml;
	static Statistics* singleton;

public:
	int getNumMaps();
	int getNumItems();
	void setNumMaps(int num);
	void setNumItems(int num);
	static Statistics* getInstance();

};