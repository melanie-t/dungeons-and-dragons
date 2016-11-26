#pragma once
#include "Observer.h"
#include "Map.h"

class SubjectMap : public Observer {
public:
	SubjectMap();
	SubjectMap(Map* m);
	~SubjectMap();
	void Update();
	void logMap();

private:
	Map *subject;
	bool showLog = true;
};
