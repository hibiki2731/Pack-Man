
#pragma once
#include "stdafx.h"

class Player :public GameObject
{
	enum Direct {
		IDLE = 0,
		RIGHT = 1,
		LEFT = -1,
		UP = -1,
		DOWN = 1
	};

public:
	//�R���X�g���N�^
	Player(int posIndex[2]);
	Player(int posIndex);


	//�X�V�֐�
	void update(char(&blockMap)[mapHeight][mapWidth],char(&objectMap)[mapHeight][mapWidth]) override;	//�Q�[���X�V
	void draw() override;	//�o�͍X�V
	void input(int key);   //���͏���

	float getPos_x() override;
	float getPos_y() override;
	float getRad() override;
	bool hasCollider() override;
	int getPosIndex_x();
	int getPosIndex_y();
	int getcurrentDirect_x();
	int getcurrentDirect_y();

	int getHp();
	int getScore();

	void collisionAct(GameObject* collider);	//�Փˎ��̏���


private:

	float radius;		//�v���C���[�̔��a

	int mPosIndex[2];	//�v���C���[��index���W
	int mPrePosIndex[2];	//�X�V�O�̃C���f�b�N�X���W
	//�`��ɗp����v���C���[�̍��W
	float x;
	float y;
	//�ړ��̖ڕW���W
	float targetPos_x;
	float targetPos_y;
	//�ڕW���W�Ƃ̋��e�͈�

	float speed;	//�ړ��̑���
	Direct nextDirect[2];	//���̌���
	Direct currentDirect[2];	//���݂̌���

	void mapView(char (&map)[mapHeight][mapWidth]);	//�f�o�b�O�p
	void updateMap(char(&map)[mapHeight][mapWidth]);	//�v���C���[�̃}�b�v�ʒu�̍X�V

	//�X�e�[�^�X
	int hp;
	int timeCounter;
	int invincibleLength;
	int score;

	//�`��p
	int sliceNum;
	int thickness;

};

