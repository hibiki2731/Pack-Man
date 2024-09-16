#pragma once
#include "stdafx.h"

class MainManager
{

public:
	MainManager();

	void init();
	void update();
	void draw();
	void exit();

	void setKey(int key);
	int getKey();

	char mBlockMap[mapHeight][mapWidth];
	char mObjectMap[mapHeight][mapWidth];
	GameState gameState;
	int mKey = 0;
	Player* player;

private:
	void setMap(char blockMap[mapHeight][mapWidth], char objectMap[mapHeight][mapWidth]);
	void loadMap();
	//void loadEnemy(std::vector<int>(&enemies));
	bool collision(GameObject* g1, GameObject* g2);
	void gameOver();
	void gameClear();
	void showStatus();

	std::vector<GameObject*> mGameObjects;
	int flagNumber;
	ofTrueTypeFont statusBar;
	int fontSize;
};

