#pragma once
#include "stdafx.h"

class MainManager
{

public:
	MainManager();

	void init();
	void update();
	void draw();
	void input(int key);
	void exit();

	char mBlockMap[mapHeight][mapWidth];
	char mObjectMap[mapHeight][mapWidth];
	GameState gameState;
	Player* player;

	void setStageNum(int stageNum);

private:
	void setMap();
	void loadMap();
	bool collision(GameObject* g1, GameObject* g2);
	void gameOver();
	void gameClear();
	void showStatus();

	std::vector<GameObject*> mGameObjects;
	int flagNumber;	//�X�e�[�W���Ƃ̃t���b�O�̍ő吔

	//�����`��֘A
	ofTrueTypeFont statusBar;	//�X�e�[�^�X�o�[
	ofTrueTypeFont canvas_pose;
	ofTrueTypeFont canvas_gameover;
	ofTrueTypeFont canvas_gameclear;

	int statusFontSize;	//�X�e�[�^�X�o�[�̃t�H���g�T�C�Y;
	int fontSize_pose;
	int fontSize_gameover;
	int fontSize_gameclear;

	//�T�E���h�֘A
	ofSoundPlayer gameBGM;
	ofSoundPlayer clearSE;
	ofSoundPlayer gameOverSE;

	//�X�e�[�W�ԍ�
	int mStageNum;
};

