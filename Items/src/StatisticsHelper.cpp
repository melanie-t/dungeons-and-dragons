#include "StatisticsHelper.h"
#include <iostream>

//! getNumMaps function
//! @retunr # of maps.
int Statistics::getNumMaps()
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		xml.FindElem("maps");

		return atoi(xml.GetData().c_str());
	}
	else
	{
		return -1; //Not a stats file.
	}
}

//! getNumItems function
//! @return # of items.
int Statistics::getNumItems()
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		xml.FindElem("items");

		return atoi(xml.GetData().c_str());
	}
	else
	{
		return -1; //Not a stats file.
	}
}

//! getNumCampaigns function
//! @retunr # of campaigns
int Statistics::getNumCampaigns()
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		xml.FindElem("campaigns");

		return atoi(xml.GetData().c_str());
	}
	else
	{
		return -1; //Not a stats file.
	}
}

//! getCharacterList function
//! gets list of characters
std::vector<std::string> Statistics::getCharacterList()
{
	std::vector<std::string> characterlist;
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		if (xml.FindElem("characters"))
		{
			xml.IntoElem();

			while (xml.FindElem())
			{
				characterlist.push_back(xml.GetData().c_str());
			}
			xml.OutOfElem();
		}
		return characterlist;
	}
	else
	{
		return characterlist; //Not a stats file.
	}
}

//! setNumMaps functions
//! sets number of maps in stats file
//! @num number of maps.
void Statistics::setNumMaps(int num)
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		xml.FindElem("maps");

		xml.SetData(num);
	}
	xml.Save("stats.xml");
}

//! setNumItems function
//! sets number of items
//! @param num, number of items
void Statistics::setNumItems(int num)
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		xml.FindElem("items");

		xml.SetData(num);
	}
	xml.Save("stats.xml");
}

//! setNumCampaigns function 
//! sets number of campaigns
//! @param num number of campaigns
void Statistics::setNumCampaigns(int num)
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		xml.FindElem("campaigns");

		xml.SetData(num);
	}
	xml.Save("stats.xml");
}

//! addCharacter function
//! adds character to file.
//! @param name character name.
void Statistics::addCharacter(std::string name)
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		if (xml.FindElem("characters"))
		{
			xml.IntoElem();
			xml.AddElem("character", name);
		}
	}
	xml.Save("stats.xml");
}

Statistics* Statistics::singleton;

//! getInstance function
//! gets singleton object
Statistics* Statistics::getInstance()
{
	if (singleton == nullptr)
		singleton = new Statistics();
	return singleton;
}