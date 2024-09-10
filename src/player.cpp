#include "stdafx.h"

//�R���X�g���N�^
Player::Player(int posIndex[2])
	: speed(tileSize/16)
{
	//�C���f�b�N�X���W
	mPosIndex[0] = posIndex[0];
	mPosIndex[1] = posIndex[1];
	mPrePosIndex[0] = mPosIndex[0];
	mPrePosIndex[1] = mPosIndex[1];

	//���W
	x = (float)(mPosIndex[0] * tileSize + tileSize / 2);
	y = (float)(mPosIndex[1] * tileSize + tileSize / 2);

	//�ڕW���W
	targetPos_x = x;
	targetPos_y = y;

	currentDirect[0] = IDLE; currentDirect[1] = IDLE;	//���݂̌���
	nextDirect[0] = IDLE; nextDirect[1] = IDLE;	//���̌���

	radius = tileSize / 2 - 1;	//�v���C���[�̔��a
	hp = 3;
	score = 0;
	invincibleLength = 100;
	timeCounter = 0;

	sliceNum = 15;
	thickness = 5;
	tag = PLAYER;

}
Player::Player(int posIndex) : speed(2) {

	//�C���f�b�N�X���W
	mPosIndex[0] = posIndex%mapWidth;
	mPosIndex[1] = posIndex/mapWidth;
	mPrePosIndex[0] = mPosIndex[0];
	mPrePosIndex[1] = mPosIndex[1];

	//���W
	x = (float)(mPosIndex[0] * tileSize + tileSize / 2);
	y = (float)(mPosIndex[1] * tileSize + tileSize / 2);

	//�ڕW���W
	targetPos_x = x;
	targetPos_y = y;

	currentDirect[0] = IDLE; currentDirect[1] = IDLE;	//���݂̌���
	nextDirect[0] = IDLE; nextDirect[1] = IDLE;	//���̌���

	radius = tileSize / 2 - 1;	//�v���C���[�̔��a

	sliceNum = 15;
	thickness = 5;
	tag = PLAYER;
}

void Player::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum) {
	//���͏���
	input(keyNum);

	//�X�V�O�̃C���f�b�N�X���W
	mPrePosIndex[0] = mPosIndex[0];
	mPrePosIndex[1] = mPrePosIndex[1];
	
	try {
		//targetPos�̍X�V
		if (targetPos_x == x && targetPos_y == y) {
			//�����̕ύX
			//�ǂ��Ȃ�������nextDirect��currentDirect�ɑ��
			if (blockMap[mPosIndex[1]][mPosIndex[0] + nextDirect[0]] <= 1 &&
				blockMap[mPosIndex[1] + nextDirect[1]][mPosIndex[0]] <= 1) {
				currentDirect[0] = nextDirect[0];
				currentDirect[1] = nextDirect[1];
			}
			//�ǂ��Ȃ�������targetPos��i�s�����֍X�V
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

	//���W�̍X�V
	x += static_cast<float>(currentDirect[0]*speed);
	y += static_cast<float>(currentDirect[1]*speed);

	//targetPos���߂����������
	if ((targetPos_x - x)* currentDirect[0] < 0) {
		x += targetPos_x - x;
	}
	if ((targetPos_y - y) * currentDirect[1] < 0) {
		y += targetPos_y - y;
	}

	//�C���f�b�N�X���W�̍X�V
	mPosIndex[0] = static_cast<int>(x / tileSize);
	mPosIndex[1] = static_cast<int>(y / tileSize);

	//�}�b�v�̍X�V
	updateMap(objectMap);
	if (keyNum == 'm') mapView(objectMap);
	
	//���G���Ԃ̃J�E���g
	if (timeCounter != 0) {
		timeCounter--;
	}
}

void Player::draw() {
	//�v���C���[�̕`��
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

	//�L�[����
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
	//�G�ƐڐG�����ꍇ
	if (dynamic_cast<Enemy*>(collider) && timeCounter == 0) {
		hp--;
		timeCounter = invincibleLength;
	}
	//�t���O�ƐڐG�����ꍇ
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

	map[mPrePosIndex[1]][mPrePosIndex[0]] = 0;	//�ړ��O�̍��W�ɂ�0
	map[mPosIndex[1]][mPosIndex[0]] = 1;		//�ړ���̍��W�ɂ�1

}
