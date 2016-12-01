//! @file MapLogger.h
//! @brief Header file for MapLogger Class
//!
#pragma once

#include "PlayerActionTypes.h"
#include <string>
using namespace std;

class MapLogger{
public:
	MapLogger();
	void Update(string character, PlayerMove move);
	void toggle();

private:
	bool showLog;
};
