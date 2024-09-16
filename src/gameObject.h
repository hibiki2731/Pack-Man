#pragma once
#include "stdafx.h"

class GameObject
{
public:
	virtual void update(char(&blockMap)[mapHeight][mapWidth],char(&objectMap)[mapHeight][mapWidth]) = 0;
	virtual void draw() = 0;
	virtual void input(int key) = 0;

	virtual float getPos_x() = 0;
	virtual float getPos_y() = 0;
	virtual float getRad() = 0;
	virtual bool hasCollider() = 0;

	Tag tag = NONE;
	bool isSurvive = true;

	//グラデーションの描画
	float3 palette(float x, float y);
	float3 palette(float x, float y, float3 a, float3 b, float3 c, float3 d);

};

