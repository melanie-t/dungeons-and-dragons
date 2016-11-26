#include "MathHelper.h"
#include <math.h>

//! getDistance function.
//! @brief get the distance between two positions
//! using pythagorean theorem.
int MathHelper::getDistance(pos positionOne, pos positionTwo)
{
	double distance = sqrt(pow((double)(positionOne.x - positionTwo.x), 2) + pow((double)(positionOne.y - positionTwo.y), 2));

	// Nguyen - had a hard time compiling because abs() was causing issues, changed it fabs()
	return fabs(distance); //Absolute value, though I don't think it's needed.
}