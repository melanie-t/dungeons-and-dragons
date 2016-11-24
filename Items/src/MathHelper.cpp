#include "MathHelper.h"
#include <math.h>

//! getDistance function.
//! @brief get the distance between two positions
//! using pythagorean theorem.
int MathHelper::getDistance(pos positionOne, pos positionTwo)
{
	double distance = sqrt(pow((double)(positionOne.x - positionTwo.x), 2) + pow((double)(positionOne.y - positionTwo.y), 2));

	return abs(distance); //Absolute value, though I don't think it's needed.
}