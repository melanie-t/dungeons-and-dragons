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
	//getters
	int getNumMaps();
	int getNumItems();
	int getNumCampaigns();
	std::vector<std::string> getCharacterList();

	//setters
	void setNumMaps(int num);
	void setNumItems(int num);
	void setNumCampaigns(int num);
	void addCharacter(std::string name);

	//instance
	static Statistics* getInstance();
};