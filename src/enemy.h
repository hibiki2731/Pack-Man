#pragma once
#include "stdafx.h"

class Enemy :public GameObject
{
public:

	struct CanThrough {
		bool front;
		bool right;
		bool left;
	};

	Enemy(int posIndex);

	void update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum) override;	//ゲーム更新
	void draw() override;

	float getPos_x() override;
	float getPos_y() override;
	float getRad() override;
	bool hasCollider() override;


private:
	float x;
	float y;
	int posIndex_x;
	int posIndex_y;

	ofColor mColor;
	float radius;
	float speed;

	int direct_x;
	int direct_y;

	float targetPos_x;
	float targetPos_y;

	//描画用
	int sliceNum;
	int thickness;
	

	void changeDirection(char(&currentMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth]);
	ofVec2f getPlayerPos(char(&objectMap)[mapHeight][mapWidth]);
};

