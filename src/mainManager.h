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

private:
	void setMap(char blockMap[mapHeight][mapWidth], char objectMap[mapHeight][mapWidth]);
	void loadMap();
	bool collision(GameObject* g1, GameObject* g2);
	void gameOver();
	void gameClear();
	void showStatus();

	std::vector<GameObject*> mGameObjects;
	int flagNumber;
	ofTrueTypeFont statusBar;
	int fontSize;

	ofSoundPlayer gameBGM;
	ofSoundPlayer clearSE;
	ofSoundPlayer gameOverSE;
};

