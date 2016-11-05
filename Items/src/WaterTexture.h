#include "GameObject.h"

class WaterTexture : public GameObject
{
public:
	WaterTexture()
	{
		GameObject(WATER);
	}
};