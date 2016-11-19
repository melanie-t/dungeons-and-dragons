#pragma once

#include "Map.h"

class Campaign
{
private:
	Map* begin;
	void setup(Map* focus);
public:
	Campaign(Map* begin);
	void setupCampaign();
	Map* getBeginningMap(){ return begin; }


	static Campaign* loadCampaign(int id);
	static Campaign* createCampaign();
};