#include "stdafx.h"

MainManager::MainManager() {

	char blockMap[mapHeight][mapWidth] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
		{2,1,2,2,1,2,2,1,2,2,2,2,2,2,1,2},
		{2,1,2,1,1,1,2,1,2,1,1,1,1,2,1,2},
		{2,1,2,1,2,1,2,1,1,1,2,2,1,1,1,2},
		{2,1,2,1,2,1,2,1,2,1,2,2,1,2,1,2},
		{2,1,2,1,1,1,2,1,2,1,1,1,1,2,1,2},
		{2,1,2,2,1,2,2,1,2,2,2,2,2,2,1,2},
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
		{2,1,2,2,2,2,2,1,2,2,2,1,2,2,1,2},
		{2,1,2,1,1,1,2,1,2,1,1,1,1,2,1,2},
		{2,1,1,1,2,1,1,1,2,1,2,2,1,2,1,2},
		{2,1,2,1,1,1,2,1,2,1,1,1,1,2,1,2},
		{2,1,2,2,2,2,2,1,2,2,1,2,2,2,1,2},
		{2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	char objectMap[mapHeight][mapWidth] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,2,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	};

	gameState = PLAY;	//gameStateの設定

	setMap(blockMap,objectMap);	//マップ情報を設定

	flagNumber = 0;
	loadMap();	//マップの読み込み
	//std::cout << flagNumber;

	
	// ステータスバーの設定。
	fontSize = 30;	//フォントサイズ
	ofTrueTypeFont::setGlobalDpi(72);

	statusBar.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
	statusBar.setLineHeight(24);       // 行間を指定する
	statusBar.setLetterSpacing(1.0);   // 文字間を指定する

}

void MainManager::update() {
	//更新
	std::vector<int> deadObjIndex;	//消去するオブジェクトのindexを保存する配列
	int index = 0;
	for (GameObject* gameObject : mGameObjects) {
		gameObject->update(mBlockMap, mObjectMap, getKey());

		//衝突処理
		//gameObjectがplayerでない、colliderがtrue、衝突判定がtrue
		if (
			gameObject != player &&
			gameObject->hasCollider() &&
			collision(player,gameObject)) {

			//衝突時に実行すること
			player->collisionAct(gameObject);

		}

		//オブジェクトが消滅した場合
		if (gameObject->isSurvive == false) {
			deadObjIndex.emplace_back(index);	//要素のindexを保存
		}
		index++;
	}
	mKey = 0;

	//オブジェクトの消去 
	for (auto index : deadObjIndex) {
		delete mGameObjects[index];	//オブジェクトのメモリ開放
		mGameObjects.erase(mGameObjects.begin() + index);	//vectorの要素を開放
	}
	mGameObjects.shrink_to_fit();	//vectorの長さを最適化

	//オブジェクトの更新後
	//playerのhpが0になったらゲームオーバー
	if (player->getHp() == 0) {
		gameOver();
	}

	if (player->getScore() == flagNumber) {
		gameClear();
	}

}

void MainManager::draw() {

	for (GameObject* gameObject : mGameObjects) {
		gameObject->draw();
	}

	//ステータスの表示
	showStatus();
}

void MainManager::setMap(char blockMap[mapHeight][mapWidth], char objectMap[mapHeight][mapWidth]){
	int y, x;
	for (y = 0; y < mapHeight; y++) {
		for (x = 0; x < mapWidth; x++) {
			mBlockMap[y][x] = blockMap[y][x];
			mObjectMap[y][x] = objectMap[y][x];
		}
	}
}

void MainManager::loadMap() {
	int y, x;
	for (y = 0; y < mapHeight; y++) {
		for (x = 0; x < mapWidth; x++) {
			int vec2[] = { x,y };
			//マップ形成
			switch (mBlockMap[y][x]) {
			case 0:
				break;
			case 1:
				mGameObjects.push_back(new Flag(y * mapWidth + x));
				flagNumber++;
				break;
			case 2:
				mGameObjects.push_back(new StoneBlock(vec2));
				break;
			}

		}
	}

	for (y = 0; y < mapHeight; y++) {
		for (x = 0; x < mapWidth; x++) {
			int vec2[] = { x,y };

			//オブジェクトの設置
			switch (mObjectMap[y][x]) {
			case 0:
				break;
			case 1:
				player = new Player(vec2);
				mGameObjects.push_back(player);
				break;
			case 2:
				mGameObjects.push_back(new Enemy(SQUARE ,y * mapWidth + x));
				break;
			case 3:
				mGameObjects.push_back(new Enemy(TRIANGELE, y * mapWidth + x));
				break;
			}
		}
	}

	//enemyにプレイヤー情報を追加
	for (GameObject *gameObject : mGameObjects) {
		if (gameObject->tag == ENEMY) {
			dynamic_cast<Enemy*>(gameObject)->setPlayerInf(player);
		}
	}
}
void MainManager::setKey(int key) {
	mKey = key;
}

int MainManager::getKey() {
	return mKey;
}

bool MainManager::collision(GameObject* g1, GameObject* g2) {
	//距離の2乗<=半径の和
	if (pow((g1->getPos_x() - g2->getPos_x()), 2) + pow((g1->getPos_y() - g2->getPos_y()), 2)
		<= pow(g1->getRad() + g2->getRad(), 2)) {
		return true;
	}
	return false;
}

void MainManager::gameOver() {

	gameState = GAMEOVER;
}

void MainManager::gameClear() {
	gameState = GAMECLEAR;
}

void MainManager::showStatus() {

	int offSet_x = 6;
	int offSet_y = 3;

	//hpの表示
	string text = "HP:"+to_string(player->getHp())+"\n"+ "SCORE:" + to_string(player->getScore());
	ofSetColor(255, 255, 255); // 色を指定
	statusBar.drawString(text, windowWidth - offSet_x *fontSize, fontSize); // 文字とポジションを指定して描画

}