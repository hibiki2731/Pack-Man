#include "stdafx.h"

MainManager::MainManager() {
	ofTrueTypeFont::setGlobalDpi(72);

	// �X�e�[�^�X�o�[�̐ݒ�B
	statusFontSize = 30;	//�t�H���g�T�C�Y
	statusBar.load("SawarabiMincho-Regular.ttf", statusFontSize); // �t�H���g�̃f�[�^���w�肷��
	statusBar.setLineHeight(30);       // �s�Ԃ��w�肷��
	statusBar.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

	//UI�t�H���g
	fontSize_pose = 80;
	canvas_pose.load("SawarabiMincho-Regular.ttf", fontSize_pose); // �t�H���g�̃f�[�^���w�肷��
	canvas_pose.setLineHeight(24);       // �s�Ԃ��w�肷��
	canvas_pose.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

	fontSize_gameover = 80;
	canvas_gameover.load("SawarabiMincho-Regular.ttf", fontSize_gameover); // �t�H���g�̃f�[�^���w�肷��
	canvas_gameover.setLineHeight(30);       // �s�Ԃ��w�肷��
	canvas_gameover.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

	fontSize_gameclear = 70;
	canvas_gameclear.load("SawarabiMincho-Regular.ttf", fontSize_gameclear); // �t�H���g�̃f�[�^���w�肷��
	canvas_gameclear.setLineHeight(24);       // �s�Ԃ��w�肷��
	canvas_gameclear.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

	//������
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

	//BGM�̐ݒ�
	gameBGM.loadSound("MusMus-CT-01.mp3");
	gameBGM.setLoop(true);
	gameBGM.setMultiPlay(true);
	gameBGM.setVolume(0.08);
	//SE�̃��[�h
	//�Q�[���N���A
	clearSE.loadSound("Igavethemeverything.ogg");
	clearSE.setMultiPlay(true);
	clearSE.setVolume(0.06);
	//�Q�[���I�[�o�[
	gameOverSE.loadSound("Ah.ogg");
	gameOverSE.setMultiPlay(true);
	gameOverSE.setVolume(0.06);

}

void MainManager::setStageNum(int stageNum) {
	mStageNum = stageNum;
}

void MainManager::init() {

	gameState = PLAY;	//gameState�̐ݒ�

	setMap();	//�}�b�v����ݒ�

	flagNumber = 0;
	loadMap();	//�}�b�v�̓ǂݍ���

	gameBGM.play();
}

void MainManager::update() {
	//�X�V
	std::vector<int> deadObjIndex;	//��������I�u�W�F�N�g��index��ۑ�����z��
	int index = 0;
	if (gameState == PLAY) {
		for (GameObject* gameObject : mGameObjects) {
			gameObject->update(mBlockMap, mObjectMap);

			//�Փˏ���
			//gameObject��player�łȂ��Acollider��true�A�Փ˔��肪true
			if (
				gameObject != player &&
				gameObject->hasCollider() &&
				collision(player, gameObject)) {

				//�Փˎ��Ɏ��s���邱��
				player->collisionAct(gameObject);

			}

			//�I�u�W�F�N�g�����ł����ꍇ
			if (gameObject->isSurvive == false) {
				deadObjIndex.emplace_back(index);	//�v�f��index��ۑ�
			}
			index++;

		}

		//�I�u�W�F�N�g�̏��� 
		for (auto index : deadObjIndex) {
			delete mGameObjects[index];	//�I�u�W�F�N�g�̃������J��
			mGameObjects.erase(mGameObjects.begin() + index);	//vector�̗v�f���J��
		}
		mGameObjects.shrink_to_fit();	//vector�̒������œK��

		//�I�u�W�F�N�g�̍X�V��
		//player��hp��0�ɂȂ�����Q�[���I�[�o�[
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

	//�|�[�Y���̏���
	if (gameState == POSE) {
		ofSetColor(0, 0, 0, 150);
		ofDrawRectangle(0,0,windowWidth,windowHeight);
		
		string text_POSE = "POSE";
		string text_R = "R : reset";
		string text_Q = "Q : to title";

		ofTrueTypeFont::setGlobalDpi(72);

		ofSetColor(255, 255, 255); // �F���w��
		canvas_pose.drawString(text_POSE, windowWidth / 2 - text_POSE.length() / 2 * fontSize_pose, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas_pose.drawString(text_R, windowWidth / 2 - text_POSE.length() / 2 * fontSize_pose - fontSize_pose, windowHeight / 2 + fontSize_pose); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas_pose.drawString(text_Q, windowWidth / 2 - text_POSE.length() / 2 * fontSize_pose - fontSize_pose, windowHeight / 2 + fontSize_pose * 2); // �����ƃ|�W�V�������w�肵�ĕ`��
	}

	//�Q�[���I�[�o�[���̏���
	if (gameState == GAMEOVER) {
		ofSetColor(0, 0, 0, 150);
		ofDrawRectangle(0, 0, windowWidth, windowHeight);
		string text = "GAMEOVER\n";
		string text_Q = "Q : to title\n";

		ofTrueTypeFont::setGlobalDpi(72);


		ofSetColor(255, 50, 50); // �F���w��
		canvas_gameover.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize_gameover, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas_gameover.drawString(text_Q, windowWidth / 2 - text.length() / 2 * fontSize_gameover + fontSize_gameover, windowHeight / 2 + fontSize_gameover); // �����ƃ|�W�V�������w�肵�ĕ`��

	}

	//�Q�[���N���A���̏���
	if (gameState == GAMECLEAR) {
		ofSetColor(0, 0, 0, 150);
		ofDrawRectangle(0, 0, windowWidth, windowHeight);
		string text = "CONGRATULATION!!\n";
		string text_Q = "Q : to title\n";

		ofTrueTypeFont::setGlobalDpi(72);


		ofSetColor(255, 255, 255); // �F���w��
		canvas_gameclear.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize_gameclear + fontSize_gameclear * 2, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas_gameclear.drawString(text_Q, windowWidth / 2 - text.length() / 2 * fontSize_gameclear + fontSize_gameclear * 5,  windowHeight / 2 + fontSize_gameclear); // �����ƃ|�W�V�������w�肵�ĕ`��

	}

	//�X�e�[�^�X�̕\��
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

	//�X�e�[�W�t�@�C���̓ǂݍ���
	std::ifstream ifs("src/stageFile/stage" + to_string(mStageNum) +".txt");
	//�ǂݍ��݂Ɏ��s�����ꍇ
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
			//�}�b�v�`��
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

			//�I�u�W�F�N�g�̐ݒu
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

	//enemy�Ƀv���C���[����ǉ�
	for (GameObject *gameObject : mGameObjects) {
		if (gameObject->tag == ENEMY) {
			dynamic_cast<Enemy*>(gameObject)->setPlayerInf(player);
		}
	}
}

void MainManager::exit() {
	for (GameObject *gameObject : mGameObjects) {
		delete gameObject;	//�I�u�W�F�N�g�̃������J��
	}
	mGameObjects.erase(mGameObjects.begin(), mGameObjects.end());

	//enemy��SE���~
	for (GameObject* gameObject : mGameObjects) {
		if (gameObject->tag == ENEMY) {
			dynamic_cast<Enemy*>(gameObject)->stopSE();
		}
	}
	gameBGM.stop();
	gameOverSE.stop();
	clearSE.stop();
}

bool MainManager::collision(GameObject* g1, GameObject* g2) {
	//������2��<=���a�̘a
	if (pow((g1->getPos_x() - g2->getPos_x()), 2) + pow((g1->getPos_y() - g2->getPos_y()), 2)
		<= pow(g1->getRad() + g2->getRad(), 2)) {
		return true;
	}
	return false;
}

void MainManager::gameOver() {
	gameBGM.stop();

	//enemy��SE���~
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
	//enemy��SE���~
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

	//hp�̕\��
	string text = "HP:"+to_string(player->getHp())+"\n"+ "SCORE:" + to_string(player->getScore());
	ofSetColor(255, 255, 255); // �F���w��
	statusBar.drawString(text, windowWidth - offSet_x *statusFontSize, statusFontSize + offSet_y); // �����ƃ|�W�V�������w�肵�ĕ`��

}