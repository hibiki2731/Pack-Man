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

}

void Enemy::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum){
	try {
		//targetPosの更新
		if (targetPos_x == x && targetPos_y == y) {

			//向きの変更
			changeDirection(blockMap);

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

}

void Enemy::draw() {

	//描画
	ofSetColor(ofColor(0, 200, 0, 255));
	ofDrawCircle(x, y, radius);
}

void Enemy::changeDirection(char(&currentMap)[mapHeight][mapWidth]) {

	try {

		int preDirect_x = direct_x;
		int preDirect_y = direct_y;

			//壁の方向を向いていたら方向転換
			if (currentMap[posIndex_y][posIndex_x + direct_x] > 1 &&
				currentMap[posIndex_y + direct_y][posIndex_x] > 1) {
				direct_x = -preDirect_y;
				direct_y = preDirect_x;

			}
			else {
				//向きの変更
				int r = rand() % 100;
				if (r <= 60) {
					//そのまま
				}
				else if (r <= 75) {
					//右を向く
					direct_x = -preDirect_y;
					direct_y = preDirect_x;
				}
				else if (r <= 90) {
					//左を向く
					direct_x = preDirect_y;
					direct_y = -preDirect_x;
				}
				else if (r < 100) {
					//後ろを向く
					direct_x = -preDirect_x;
					direct_y = -preDirect_y;
				}
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