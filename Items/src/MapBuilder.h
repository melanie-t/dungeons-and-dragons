#pragma once
#include "Map.h"
#include "Character.h"

class MapBuilder
{
protected:
	Map* m_Map;
public:
	~MapBuilder(){ delete m_Map; }
	Map* getMap(){ return this->m_Map; }

	void createNewMap(){ this->m_Map = new Map(); };

	virtual bool loadMap(int id) = 0;
};