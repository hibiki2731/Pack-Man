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

	Enemy(EnemyType type, int posIndex);

	void update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum) override;	//�Q�[���X�V
	void draw() override;

	float getPos_x() override;
	float getPos_y() override;
	float getRad() override;
	bool hasCollider() override;

	//�v���C���[�����擾
	void setPlayerInf(Player* player);


private:
	//���W
	float x;
	float y;
	int posIndex_x;
	int posIndex_y;
	int firstPosIndex_x;
	int firstPosIndex_y;
	//����
	int direct_x;
	int direct_y;

	float nextPos_x;
	float nextPos_y;
	ofVec2f targetPos;

	float speed;
	float rotateSpeed;

	//�`��p
	float radius;
	int sliceNum;
	int thickness;
	float3 colorA;
	float3 colorB;
	float3 colorC;
	float3 colorD;

	//�G���ʕϐ�
	EnemyType mType;
	
	//�v���C���[���
	Player *mPlayer;

	void changeDirection(char(&currentMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth]);
	ofVec2f getPlayerPos(char(&objectMap)[mapHeight][mapWidth]);
};

