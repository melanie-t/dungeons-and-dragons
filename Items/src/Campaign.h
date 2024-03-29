//! @file Campaign.h
//! @brief Header file for Campaign Class
//!
#pragma once

#include "Map.h"
#include "Character.h"

class Campaign
{
private:
	Map* begin;
	void setup(Map* focus);
	int id;
public:
	Campaign(Map* begin, bool setup = true, int id = (Statistics::getInstance()->getNumCampaigns() + 1));
	void setupCampaign();
	void saveCampaign();
	Map* getBeginningMap(){ return begin; }
	void setBeginningMap(Map* map);


	static Campaign* loadCampaign(int id, Character* player = nullptr);
	static Campaign* createCampaign();
};