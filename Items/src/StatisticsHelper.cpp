#include "StatisticsHelper.h"

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

void Statistics::setNumMaps(int num)
{
	xml.Load("stats.xml");
	if (xml.FindElem("stats"))
	{
		xml.IntoElem();
		xml.FindElem("maps");

		xml.SetData(num);
	}
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
}