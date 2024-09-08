#include "stdafx.h"

Enemy::Enemy(int posIndex) {

	x = (float)((posIndex % mapWidth) * tileSize + tileSize / 2);
	y = (float)((posIndex / mapWidth) * tileSize + tileSize / 2);

	posIndex_x = posIndex % mapWidth;
	posIndex_y = posIndex / mapWidth;

	mColor = { 100,100,100,255 };//�G�l�~�[�̐F
	radius = tileSize / 2 - 1;	//�G�l�~�[�̔��a
	speed = tileSize/20;

	direct_x = 1;
	direct_y = 0;

	targetPos_x = x;
	targetPos_y = y;

}

void Enemy::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum){
	try {
		//targetPos�̍X�V
		if (targetPos_x == x && targetPos_y == y) {

			//�����̕ύX
			changeDirection(blockMap);

			//�ǂ��Ȃ�������targetPos���X�V����
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

	//���W�̍X�V
	x += static_cast<float>(direct_x * speed);
	y += static_cast<float>(direct_y * speed);

	//targetPos���߂����������
	if ((targetPos_x - x) * direct_x < 0) {
		x += targetPos_x - x;
	}
	if ((targetPos_y - y) * direct_y < 0) {
		y += targetPos_y - y;
	}

	//�C���f�b�N�X���W�̍X�V
	posIndex_x = static_cast<int>(x / tileSize);
	posIndex_y = static_cast<int>(y / tileSize);

}

void Enemy::draw() {

	//�`��
	ofSetColor(ofColor(0, 200, 0, 255));
	ofDrawCircle(x, y, radius);
}

void Enemy::changeDirection(char(&currentMap)[mapHeight][mapWidth]) {

	try {

		int preDirect_x = direct_x;
		int preDirect_y = direct_y;

			//�ǂ̕����������Ă���������]��
			if (currentMap[posIndex_y][posIndex_x + direct_x] > 1 &&
				currentMap[posIndex_y + direct_y][posIndex_x] > 1) {
				direct_x = -preDirect_y;
				direct_y = preDirect_x;

			}
			else {
				//�����̕ύX
				int r = rand() % 100;
				if (r <= 60) {
					//���̂܂�
				}
				else if (r <= 75) {
					//�E������
					direct_x = -preDirect_y;
					direct_y = preDirect_x;
				}
				else if (r <= 90) {
					//��������
					direct_x = preDirect_y;
					direct_y = -preDirect_x;
				}
				else if (r < 100) {
					//��������
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