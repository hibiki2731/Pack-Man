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

	//文字描画関連
	ofTrueTypeFont statusBar;	//ステータスバー
	ofTrueTypeFont canvas_pose;
	ofTrueTypeFont canvas_gameover;
	ofTrueTypeFont canvas_gameclear;

	int statusFontSize;	//ステータスバーのフォントサイズ;
	int fontSize_pose;
	int fontSize_gameover;
	int fontSize_gameclear;

	//サウンド関連
	ofSoundPlayer gameBGM;
	ofSoundPlayer clearSE;
	ofSoundPlayer gameOverSE;

	//ステージ番号
	int mStageNum;
};

