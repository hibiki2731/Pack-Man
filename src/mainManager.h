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
	int flagNumber;	//ステージごとのフラッグの最大数
	ofTrueTypeFont statusBar;	//ステータスバー
	int fontSize;	//ステータスバーのフォントサイズ

	//サウンド関連
	ofSoundPlayer gameBGM;
	ofSoundPlayer clearSE;
	ofSoundPlayer gameOverSE;

	//ステージ番号
	int mStageNum;
};

