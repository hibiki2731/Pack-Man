#include "stdafx.h"

MainManager::MainManager() {
	// ステータスバーの設定。
	fontSize = 30;	//フォントサイズ
	ofTrueTypeFont::setGlobalDpi(72);

	statusBar.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
	statusBar.setLineHeight(24);       // 行間を指定する
	statusBar.setLetterSpacing(1.0);   // 文字間を指定する

	//初期化
	flagNumber = 0;
	gameState = TITLE;
	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			mBlockMap[y][x] = 0;
			mObjectMap[y][x] = 0;
		}
	}
	player = nullptr;
	mStageNum = 2;

	//BGMの設定
	gameBGM.loadSound("MusMus-CT-01.mp3");
	gameBGM.setLoop(true);
	gameBGM.setMultiPlay(true);
	gameBGM.setVolume(0.08);
	//SEのロード
	//ゲームクリア
	clearSE.loadSound("Igavethemeverything.ogg");
	clearSE.setMultiPlay(true);
	clearSE.setVolume(0.08);
	//ゲームオーバー
	gameOverSE.loadSound("Ah.ogg");
	gameOverSE.setMultiPlay(true);
	gameOverSE.setVolume(0.08);

}

void MainManager::setStageNum(int stageNum) {
	mStageNum = stageNum;
}

void MainManager::init() {

	gameState = PLAY;	//gameStateの設定

	setMap();	//マップ情報を設定

	flagNumber = 0;
	loadMap();	//マップの読み込み

	gameBGM.play();
}

void MainManager::update() {
	//更新
	std::vector<int> deadObjIndex;	//消去するオブジェクトのindexを保存する配列
	int index = 0;
	if (gameState == PLAY) {
		for (GameObject* gameObject : mGameObjects) {
			gameObject->update(mBlockMap, mObjectMap);

			//衝突処理
			//gameObjectがplayerでない、colliderがtrue、衝突判定がtrue
			if (
				gameObject != player &&
				gameObject->hasCollider() &&
				collision(player, gameObject)) {

				//衝突時に実行すること
				player->collisionAct(gameObject);

			}

			//オブジェクトが消滅した場合
			if (gameObject->isSurvive == false) {
				deadObjIndex.emplace_back(index);	//要素のindexを保存
			}
			index++;

		}

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

}

void MainManager::draw() {

	for (GameObject* gameObject : mGameObjects) {
		gameObject->draw();
	}

	//ポーズ中の処理
	if (gameState == POSE) {
		ofTrueTypeFont canvas;
		string text_POSE = "POSE\n";
		string text_R = "R : reset\n";
		string text_Q = "Q : to title\n";
		int fontSize = 80;
		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
		canvas.setLineHeight(30);       // 行間を指定する
		canvas.setLetterSpacing(1.0);   // 文字間を指定する

		ofSetColor(255, 255, 255); // 色を指定
		canvas.drawString(text_POSE, windowWidth / 2 - text_POSE.length() / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
		canvas.drawString(text_R, windowWidth / 2 - text_POSE.length() / 2 * fontSize - fontSize, windowHeight / 2 + fontSize); // 文字とポジションを指定して描画
		canvas.drawString(text_Q, windowWidth / 2 - text_POSE.length() / 2 * fontSize - fontSize, windowHeight / 2 + fontSize * 2); // 文字とポジションを指定して描画
	}

	//ゲームオーバー時の処理
	if (gameState == GAMEOVER) {
		ofTrueTypeFont canvas;
		string text = "GAMEOVER\n";
		string text_Q = "Q : to title\n";
		int fontSize = 80;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
		canvas.setLineHeight(24);       // 行間を指定する
		canvas.setLetterSpacing(1.0);   // 文字間を指定する

		ofSetColor(255, 50, 50); // 色を指定
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
		canvas.drawString(text_Q, windowWidth / 2 - text.length() / 2 * fontSize + fontSize, windowHeight / 2 + fontSize); // 文字とポジションを指定して描画

	}

	//ゲームクリア時の処理
	if (gameState == GAMECLEAR) {
		ofTrueTypeFont canvas;
		string text = "CONGRATULATION!!\n";
		string text_Q = "Q : to title\n";

		int fontSize = 60;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
		canvas.setLineHeight(24);       // 行間を指定する
		canvas.setLetterSpacing(1.0);   // 文字間を指定する

		ofSetColor(255, 255, 255); // 色を指定
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
		canvas.drawString(text_Q, windowWidth / 2 - text.length() / 2 * fontSize + fontSize * 3,  windowHeight / 2 + fontSize); // 文字とポジションを指定して描画

	}

	//ステータスの表示
	showStatus();
	
}

void MainManager::input(int key) {

	for (GameObject *gameObject : mGameObjects) {
		gameObject->input(key);
	}

	switch (key)
	{
	case 'p':
		if (gameState == PLAY) {
			gameState = POSE;

		}
		else if (gameState == POSE) {
			gameState = PLAY;
		}
		break;
	case 'r':
		if (gameState == POSE) {
			exit();
			init();
			gameState = PLAY;
		}
		break;
	case 'q':
		if (gameState == POSE || gameState == GAMECLEAR || gameState == GAMEOVER) {
			exit();
			gameState = TITLE;
		}
		break;
	case 'c':
		gameClear();
		break;
	default:
		break;
	}
}

void MainManager::setMap(){

	//ステージファイルの読み込み
	std::ifstream ifs("src/stageFile/stage" + to_string(mStageNum) +".txt");
	//読み込みに失敗した場合
	if (!ifs) {
		cerr << "Error : file not opned." << endl;
		throw;
	}

	int y, x;
	for (y = 0; y < mapHeight; y++) {
		for (x = 0; x < mapWidth; x++) {
			char num;
			ifs >> num;
			mBlockMap[y][x] = static_cast<int>(num - '0');
		}
	}
	for (y = 0; y < mapHeight; y++) {
		for (x = 0; x < mapWidth; x++) {
			char num;
			ifs >> num;
			mObjectMap[y][x] = static_cast<int>(num - '0');
		}
	}
	ifs.close();

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
			case 4:
				mGameObjects.push_back(new Enemy(RED, y * mapWidth + x));
				break;
			default:
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

void MainManager::exit() {
	for (GameObject *gameObject : mGameObjects) {
		delete gameObject;	//オブジェクトのメモリ開放
	}
	mGameObjects.erase(mGameObjects.begin(), mGameObjects.end());

	gameBGM.stop();
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
	gameBGM.stop();

	//enemyのSEを停止
	for (GameObject* gameObject : mGameObjects) {
		if (gameObject->tag == ENEMY) {
			dynamic_cast<Enemy*>(gameObject)->stopSE();
		}
	}
	gameOverSE.play();
	gameState = GAMEOVER;
}

void MainManager::gameClear() {
	gameBGM.stop();
	//enemyのSEを停止
	for (GameObject* gameObject : mGameObjects) {
		if (gameObject->tag == ENEMY) {
			dynamic_cast<Enemy*>(gameObject)->stopSE();
		}
	}
	clearSE.play();
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