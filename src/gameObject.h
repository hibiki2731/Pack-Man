#pragma once
#include "stdafx.h"

class GameObject
{
public:
	virtual void update(char(&blockMap)[mapHeight][mapWidth],char(&objectMap)[mapHeight][mapWidth], int keyNum) = 0;
	virtual void draw() = 0;

	virtual float getPos_x() = 0;
	virtual float getPos_y() = 0;
	virtual float getRad() = 0;
	virtual bool hasCollider() = 0;

	bool isSurvive = true;

};

