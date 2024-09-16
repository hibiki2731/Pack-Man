#pragma once
#include "stdafx.h"

class Block : public GameObject {
public:


	void update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth]) override;	//ÉQÅ[ÉÄçXêV
	void draw() override;
	void input(int key) override;

	float getPos_x() override;
	float getPos_y() override;
	float getRad() override;
	bool hasCollider() override;

	Block(int posIndex[2]);
	Block(int posIndex);
	ofColor mColor;

private:
	float x;
	float y;

	int sliceNum;

};

class StoneBlock :public Block {
public:

	StoneBlock(int posIndex[2]);
	StoneBlock(int posIndex);
};