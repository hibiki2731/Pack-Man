#include "stdafx.h"

//コンストラクタ
Player::Player(int posIndex[2])
	: speed(tileSize/16)
{
	//インデックス座標
	mPosIndex[0] = posIndex[0];
	mPosIndex[1] = posIndex[1];
	mPrePosIndex[0] = mPosIndex[0];
	mPrePosIndex[1] = mPosIndex[1];

	//座標
	x = (float)(mPosIndex[0] * tileSize + tileSize / 2);
	y = (float)(mPosIndex[1] * tileSize + tileSize / 2);

	//目標座標
	targetPos_x = x;
	targetPos_y = y;

	currentDirect[0] = IDLE; currentDirect[1] = IDLE;	//現在の向き
	nextDirect[0] = IDLE; nextDirect[1] = IDLE;	//次の向き

	radius = tileSize / 2 - 1;	//プレイヤーの半径
	hp = 3;
	score = 0;
	invincibleLength = 100;
	timeCounter = 0;

	sliceNum = 15;
	thickness = 5;
	tag = PLAYER;

}
Player::Player(int posIndex) : speed(2) {

	//インデックス座標
	mPosIndex[0] = posIndex%mapWidth;
	mPosIndex[1] = posIndex/mapWidth;
	mPrePosIndex[0] = mPosIndex[0];
	mPrePosIndex[1] = mPosIndex[1];

	//座標
	x = (float)(mPosIndex[0] * tileSize + tileSize / 2);
	y = (float)(mPosIndex[1] * tileSize + tileSize / 2);

	//目標座標
	targetPos_x = x;
	targetPos_y = y;

	currentDirect[0] = IDLE; currentDirect[1] = IDLE;	//現在の向き
	nextDirect[0] = IDLE; nextDirect[1] = IDLE;	//次の向き

	radius = tileSize / 2 - 1;	//プレイヤーの半径

	sliceNum = 15;
	thickness = 5;
	tag = PLAYER;
}

void Player::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum) {
	//入力処理
	input(keyNum);

	//更新前のインデックス座標
	mPrePosIndex[0] = mPosIndex[0];
	mPrePosIndex[1] = mPrePosIndex[1];
	
	try {
		//targetPosの更新
		if (targetPos_x == x && targetPos_y == y) {
			//向きの変更
			//壁がなかったらnextDirectをcurrentDirectに代入
			if (blockMap[mPosIndex[1]][mPosIndex[0] + nextDirect[0]] <= 1 &&
				blockMap[mPosIndex[1] + nextDirect[1]][mPosIndex[0]] <= 1) {
				currentDirect[0] = nextDirect[0];
				currentDirect[1] = nextDirect[1];
			}
			//壁がなかったらtargetPosを進行方向へ更新
			if (blockMap[mPosIndex[1]][mPosIndex[0] + currentDirect[0]] <= 1 &&
				blockMap[mPosIndex[1] + currentDirect[1]][mPosIndex[0]] <= 1) {
				targetPos_x = x + currentDirect[0] * tileSize;
				targetPos_y = y + currentDirect[1] * tileSize;
			}
		}
	}
	catch(exception e){
		currentDirect[0] = IDLE;
		currentDirect[1] = IDLE;
	}

	//座標の更新
	x += static_cast<float>(currentDirect[0]*speed);
	y += static_cast<float>(currentDirect[1]*speed);

	//targetPosを過ぎたら微調整
	if ((targetPos_x - x)* currentDirect[0] < 0) {
		x += targetPos_x - x;
	}
	if ((targetPos_y - y) * currentDirect[1] < 0) {
		y += targetPos_y - y;
	}

	//インデックス座標の更新
	mPosIndex[0] = static_cast<int>(x / tileSize);
	mPosIndex[1] = static_cast<int>(y / tileSize);

	//マップの更新
	updateMap(objectMap);
	if (keyNum == 'm') mapView(objectMap);
	
	//無敵時間のカウント
	if (timeCounter != 0) {
		timeCounter--;
	}
}

void Player::draw() {
	//プレイヤーの描画
	for (int i = 0; i < sliceNum; i++) {
		float3 playerCol = palette(x + radius * cos(2 * PI / sliceNum * (i + 1 / 2)), y + radius * sin(2 * PI / sliceNum * (i + 1 / 2)));
		if (timeCounter == 0)
			ofSetColor(ofColor(playerCol.x, playerCol.y, playerCol.z, 255));
		else {
			ofSetColor(ofColor(playerCol.x, playerCol.y, playerCol.z, 255 * (timeCounter % 6) / 5));
		}
		for (int t = 0; t < thickness; t++) {
			float r = radius - 0.4 * t;

			ofDrawLine(x + r * cos(2* PI / sliceNum * i), y + r* sin(2 * PI / sliceNum * i), x + r * cos(2 * PI / sliceNum * (i+1)), y + r*sin(2 * PI / sliceNum * (i+1)));
		}
	}

}

void Player::input(int keyNum) {

	//キー入力
	switch (keyNum) {
	case OF_KEY_LEFT:
		nextDirect[0] = LEFT;
		nextDirect[1] = IDLE;
		break;
	case OF_KEY_RIGHT:
		nextDirect[0] = RIGHT;
		nextDirect[1] = IDLE;
		break;
	case OF_KEY_UP:
		nextDirect[0] = IDLE;
		nextDirect[1] = UP;
		break;
	case OF_KEY_DOWN:
		nextDirect[0] = IDLE;
		nextDirect[1] = DOWN;
		break;
	}
}

float Player::getPos_x() {
	return x;
}

float Player::getPos_y() {
	return y;
}
float Player::getRad() {
	return radius;
}
bool Player::hasCollider() {
	return true;
}

int Player::getHp() {
	return hp;
}
int Player::getScore() {
	return score;
}

void Player::collisionAct(GameObject* collider) {
	//敵と接触した場合
	if (dynamic_cast<Enemy*>(collider) && timeCounter == 0) {
		hp--;
		timeCounter = invincibleLength;
	}
	//フラグと接触した場合
	if (dynamic_cast<Flag*>(collider)) {
		score++;

		collider->isSurvive = false;
	}
}

void Player::mapView(char(&map)[mapHeight][mapWidth]){

	int i, t;

	for (i = 0; i < mapHeight; i++) {
		for (t = 0; t < mapWidth; t++) {
			int value = map[i][t];
			std::cout << value;
		}
		std::cout << endl;
	}
}

void Player::updateMap(char(&map)[mapHeight][mapWidth]) {

	map[mPrePosIndex[1]][mPrePosIndex[0]] = 0;	//移動前の座標には0
	map[mPosIndex[1]][mPosIndex[0]] = 1;		//移動後の座標には1

}
