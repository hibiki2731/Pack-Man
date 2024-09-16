#include "stdafx.h"

Enemy::Enemy(EnemyType type, int posIndex) {

	x = static_cast<float>(((posIndex % mapWidth) * tileSize + tileSize / 2));
	y = static_cast<float>(((posIndex / mapWidth) * tileSize + tileSize / 2));

	posIndex_x = posIndex % mapWidth;
	posIndex_y = posIndex / mapWidth;
	firstPosIndex_x = posIndex_x;
	firstPosIndex_y = posIndex_y;


	radius = tileSize / 2 - 1;	//エネミーの半径

	direct_x = 1;
	direct_y = 0;

	nextPos_x = x;
	nextPos_y = y;
	targetPos = { x ,y };

	tag = ENEMY;
	mType = type;

	colorA = { 0.731, 3, 0.53 };
	colorB = { 0.247, 0.752, 0.453 };
	colorC = { 0.785, 0.265, 0.241 };
	colorD = { 0.138, 1.918, 0.837 };

	//敵のタイプ別パラメータ
	switch (type)
	{
	case SQUARE:
		sliceNum = 4;
		thickness = 8;
		rotateSpeed = 1;
		speed = tileSize / 20;
		break;
	case TRIANGELE:
		sliceNum = 3;
		thickness = 8;
		rotateSpeed = 1;
		speed = tileSize / 20;
		break;
	case RED:
		sliceNum = 6;
		thickness = 8;
		rotateSpeed = 1;
		speed = tileSize / 20;
		break;

	default:
		sliceNum = 4;
		thickness = 8;
		rotateSpeed = 1;
		speed = tileSize / 20;
		break;
	}

}

void Enemy::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum){
	try {
		//targetPosの更新
		if (nextPos_x == x && nextPos_y == y) {

			//向きの変更
			changeDirection(blockMap,objectMap);

			//壁がなかったらtargetPosを更新する
			if (blockMap[posIndex_y][posIndex_x + direct_x] <= 1 &&
				blockMap[posIndex_y + direct_y][posIndex_x] <= 1) {
				nextPos_x = x + direct_x * tileSize;
				nextPos_y = y + direct_y * tileSize;
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
	if ((nextPos_x - x) * direct_x < 0) {
		x += nextPos_x - x;
	}
	if ((nextPos_y - y) * direct_y < 0) {
		y += nextPos_y - y;
	}

	//インデックス座標の更新
	posIndex_x = static_cast<int>(x / tileSize);
	posIndex_y = static_cast<int>(y / tileSize);

}

void Enemy::draw() {

	//敵の描画
	for (int i = 0; i < sliceNum; i++) {
		float3 enemyCol = palette(x + radius * cos(2 * PI / sliceNum * (i + 1 / 2)), y + radius * sin(2 * PI / sliceNum * (i + 1 / 2)), colorA, colorB, colorC, colorD);
		ofSetColor(ofColor(enemyCol.x, enemyCol.y, enemyCol.z, 255));

		for (int t = 0; t < thickness; t++) {
			float r = radius - 0.4 * t;
			ofDrawLine(x + r * cos(2 * PI / sliceNum * i + ofGetElapsedTimef() ), y + r * sin(2 * PI / sliceNum * i + ofGetElapsedTimef() ), x + r * cos(2 * PI / sliceNum * (i + 1) + ofGetElapsedTimef() ), y + r * sin(2 * PI / sliceNum * (i + 1) + ofGetElapsedTimef() ));
		}
	}

	ofDrawCircle(targetPos * tileSize + tileSize * 0.5, radius / 2);

}

void Enemy::changeDirection(char(&currentMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth]) {

	try {

		int preDirect_x = direct_x;
		int preDirect_y = direct_y;

		ofVec2f playerPos = {static_cast<float>(mPlayer->getPosIndex_x()),static_cast<float>(mPlayer->getPosIndex_y())};
		switch (mType)
		{
		case SQUARE:
			//プレイヤーを追跡
			targetPos = playerPos;
			break;
		case TRIANGELE:
			//プレイヤー追跡の2マス先を追跡
			targetPos.x = playerPos.x + static_cast<float>(mPlayer->getcurrentDirect_x()) * 2;
			targetPos.y = playerPos.y + static_cast<float>(mPlayer->getcurrentDirect_y()) * 2;
			break;
		case RED:
			if (std::hypotf(firstPosIndex_x - playerPos.x, firstPosIndex_y - playerPos.y) <= 5) {
				targetPos = playerPos;
				speed = tileSize / 10;
				rotateSpeed = 3;
				colorA = { 0.5, 0.5, 0.5 };
				colorB = { 0.49, -0.5, -0.5 };
				colorC = {3, -1.5, -1.5};
				colorD = {0, 0, 0};
			}
			else {
				targetPos = {static_cast<float>(firstPosIndex_x),static_cast<float>(firstPosIndex_y) };
				speed = tileSize / 20;
				rotateSpeed = 1;
				colorA = { 0.731, 3, 0.53 };
				colorB = { 0.247, 0.752, 0.453 };
				colorC = { 0.785, 0.265, 0.241 };
				colorD = { 0.138, 1.918, 0.837 };
			}
			break;

		default:
			break;
		}

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
		//右
		if (canThrough.right && sMin > std::hypotf(targetPos.x - (posIndex_x - preDirect_y), targetPos.y - (posIndex_y + preDirect_x))) {
			sMin = std::hypotf(targetPos.x - (posIndex_x - preDirect_y), targetPos.y - (posIndex_y + preDirect_x));
			direct_x = -preDirect_y;
			direct_y = preDirect_x;
		}
		//左
		if (canThrough.left && sMin > std::hypotf(targetPos.x - (posIndex_x + preDirect_y), targetPos.y - (posIndex_y - preDirect_x))) {
			sMin = std::hypotf(targetPos.x - (posIndex_x + preDirect_y), targetPos.y - (posIndex_y - preDirect_x));
			direct_x = preDirect_y;
			direct_y = -preDirect_x;
		}
		//前
		if (canThrough.front && sMin > std::hypotf(targetPos.x - (posIndex_x + preDirect_x), targetPos.y - (posIndex_y + preDirect_y))) {
			sMin = std::hypotf(targetPos.x - (posIndex_x + preDirect_x), targetPos.y - (posIndex_y + preDirect_y));
			direct_x = preDirect_x;
			direct_y = preDirect_y;
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

void Enemy::setPlayerInf(Player *player) {
	mPlayer = player;
}