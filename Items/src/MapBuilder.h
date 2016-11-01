#include "Map.h"

class MapBuilder
{
protected:
	Map* m_Map;
public:
	Map* getMap(){ return this->m_Map; }

	void createNewMap(){ this->m_Map = new Map(); };

	virtual void setNumRows() = 0;
	virtual void setNumColumns() = 0;
	virtual void buildObjects() = 0;
};