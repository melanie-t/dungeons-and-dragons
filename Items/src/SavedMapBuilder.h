#include "MapBuilder.h"

class SavedMapBuilder : MapBuilder
{
public:
	virtual void setNumRows();
	virtual void setNumColumns();
	virtual void buildObjects();
};