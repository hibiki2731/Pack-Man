#include "stdafx.h"

Enemy::Enemy(int posIndex) {

	x = (float)((posIndex % mapWidth) * tileSize + tileSize / 2);
	y = (float)((posIndex / mapWidth) * tileSize + tileSize / 2);

	posIndex_x = posIndex % mapWidth;
	posIndex_y = posIndex / mapWidth;

	mColor = { 100,100,100,255 };//エネミーの色
	radius = tileSize / 2 - 1;	//エネミーの半径
	speed = tileSize/20;

	direct_x = 1;
	direct_y = 0;

	targetPos_x = x;
	targetPos_y = y;

	sliceNum = 4;
	thickness = 8;
	tag = ENEMY;

}

void Enemy::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum){
	try {
		//targetPosの更新
		if (targetPos_x == x && targetPos_y == y) {

			//向きの変更
			changeDirection(blockMap,objectMap);

			//壁がなかったらtargetPosを更新する
			if (blockMap[posIndex_y][posIndex_x + direct_x] <= 1 &&
				blockMap[posIndex_y + direct_y][posIndex_x] <= 1) {
				targetPos_x = x + direct_x * tileSize;
				targetPos_y = y + direct_y * tileSize;
			}
		}
	}
	catch (exception e) {
		direct_x = 0;
		direct_y = 0;
	}

	//座標の更新
	x += static_cast<float>(direct_x * speed);
	y += static_cast<float>(direct_y * speed);

	//targetPosを過ぎたら微調整
	if ((targetPos_x - x) * direct_x < 0) {
		x += targetPos_x - x;
	}
	if ((targetPos_y - y) * direct_y < 0) {
		y += targetPos_y - y;
	}

	//インデックス座標の更新
	posIndex_x = static_cast<int>(x / tileSize);
	posIndex_y = static_cast<int>(y / tileSize);

	sliceNum = 4;
	thickness = 8;
	tag = ENEMY;
}

void Enemy::draw() {

	//敵の描画
	for (int i = 0; i < sliceNum; i++) {
		float3 enemyCol = palette(x + radius * cos(2 * PI / sliceNum * (i + 1 / 2)), y + radius * sin(2 * PI / sliceNum * (i + 1 / 2)));
		ofSetColor(ofColor(enemyCol.x, enemyCol.y, enemyCol.z, 255));

		for (int t = 0; t < thickness; t++) {
			float r = radius - 0.4 * t;
			ofDrawLine(x + r * cos(2 * PI / sliceNum * i), y + r * sin(2 * PI / sliceNum * i), x + r * cos(2 * PI / sliceNum * (i + 1)), y + r * sin(2 * PI / sliceNum * (i + 1)));
		}
	}

	ofDrawCircle(targetPos_x, targetPos_y, radius / 2);

}

void Enemy::changeDirection(char(&currentMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth]) {

	try {

		int preDirect_x = direct_x;
		int preDirect_y = direct_y;

		ofVec2f playerPos = getPlayerPos(objectMap);
		//壁がある方向を探す
		CanThrough canThrough = { false, false, false };
		//前
		if (currentMap[posIndex_y + direct_y][posIndex_x + direct_x] <= 1) canThrough.front = true;
		//右
		if (currentMap[posIndex_y + preDirect_x][posIndex_x - preDirect_y] <= 1) canThrough.right = true;
		//左
		if (currentMap[posIndex_y - preDirect_x][posIndex_x + preDirect_y] <= 1) canThrough.left = true;
		
		//最短距離を探す
		int sMin = 1000;
		//前
		if (canThrough.front && sMin > std::hypotf(playerPos.x - (posIndex_x + preDirect_x), playerPos.y - (posIndex_y + preDirect_y))) {
			sMin = std::hypotf(playerPos.x - (posIndex_x + preDirect_x), playerPos.y - (posIndex_y + preDirect_y));
			direct_x = preDirect_x;
			direct_y = preDirect_y;
		}
		//右
		if (canThrough.right && sMin > std::hypotf(playerPos.x - (posIndex_x - preDirect_y), playerPos.y - (posIndex_y + preDirect_x))) {
			sMin = std::hypotf(playerPos.x - (posIndex_x - preDirect_y), playerPos.y - (posIndex_y + preDirect_x));
			direct_x = -preDirect_y;
			direct_y = preDirect_x;
		}
		//左
		if (canThrough.left && sMin > std::hypotf(playerPos.x - (posIndex_x + preDirect_y), playerPos.y - (posIndex_y - preDirect_x))) {
			//sMin = std::hypotf(playerPos.x - (posIndex_x + preDirect_y), playerPos.y - (posIndex_y - preDirect_x));
			direct_x = preDirect_y;
			direct_y = -preDirect_x;
		}


	}
	catch (exception e){
		direct_x = 0;
		direct_y = 0;
	}

}

float Enemy::getPos_x() {
	return x;
}
float Enemy::getPos_y() {
	return y;
}
float Enemy::getRad() {
	return radius;
}
bool Enemy::hasCollider() {
	return true;
}

ofVec2f Enemy::getPlayerPos(char(&objectMap)[mapHeight][mapWidth]) {
	ofVec2f vec2 = { 0,0, };
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (objectMap[y][x] == 1) {
				vec2 = { static_cast<float>(x),static_cast<float>(y) };
				return vec2;
			}
		}
	}
	return vec2;
}