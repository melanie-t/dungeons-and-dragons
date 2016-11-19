#pragma once

#include <string>
#include <vector>

#include "Markup.h"

class Statistics
{
private:
	CMarkup xml;
	static Statistics* singleton;

public:
	int getNumMaps();
	int getNumItems();
	std::vector<std::string> getCharacterList();

	void setNumMaps(int num);
	void setNumItems(int num);
	void addCharacter(std::string name);
	static Statistics* getInstance();

};