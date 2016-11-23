#include "StatisticsHelper.h"
#include <iostream>

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

Statistics* Statistics::getInstance()
{
	if (singleton == nullptr)
		singleton = new Statistics();
	return singleton;
}