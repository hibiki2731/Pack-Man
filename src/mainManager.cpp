#include "stdafx.h"

MainManager::MainManager() {
}

void MainManager::init() {
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
		{0,4,0,0,0,0,0,0,0,0,0,0,3,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	};

	gameState = PLAY;	//gameState�̐ݒ�

	setMap(blockMap, objectMap);	//�}�b�v����ݒ�

	flagNumber = 0;
	loadMap();	//�}�b�v�̓ǂݍ���
	//std::cout << flagNumber;


	// �X�e�[�^�X�o�[�̐ݒ�B
	fontSize = 30;	//�t�H���g�T�C�Y
	ofTrueTypeFont::setGlobalDpi(72);

	statusBar.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
	statusBar.setLineHeight(24);       // �s�Ԃ��w�肷��
	statusBar.setLetterSpacing(1.0);   // �����Ԃ��w�肷��
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
		ofTrueTypeFont canvas;
		string text_POSE = "POSE\n";
		string text_R = "R : reset\n";
		string text_Q = "Q : to title\n";
		int fontSize = 80;
		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
		canvas.setLineHeight(30);       // �s�Ԃ��w�肷��
		canvas.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

		ofSetColor(255, 255, 255); // �F���w��
		canvas.drawString(text_POSE, windowWidth / 2 - text_POSE.length() / 2 * fontSize, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas.drawString(text_R, windowWidth / 2 - text_POSE.length() / 2 * fontSize - fontSize, windowHeight / 2 + fontSize); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas.drawString(text_Q, windowWidth / 2 - text_POSE.length() / 2 * fontSize - fontSize, windowHeight / 2 + fontSize * 2); // �����ƃ|�W�V�������w�肵�ĕ`��
	}

	//�Q�[���I�[�o�[���̏���
	if (gameState == GAMEOVER) {
		ofTrueTypeFont canvas;
		string text = "GAMEOVER\n";
		string text_Q = "Q : to title\n";
		int fontSize = 80;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
		canvas.setLineHeight(24);       // �s�Ԃ��w�肷��
		canvas.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

		ofSetColor(255, 50, 50); // �F���w��
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas.drawString(text_Q, windowWidth / 2 - text.length() / 2 * fontSize + fontSize, windowHeight / 2 + fontSize); // �����ƃ|�W�V�������w�肵�ĕ`��

	}

	//�Q�[���N���A���̏���
	if (gameState == GAMECLEAR) {
		ofTrueTypeFont canvas;
		string text = "CONGRATULATION!!\n";
		string text_Q = "Q : to title\n";

		int fontSize = 60;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
		canvas.setLineHeight(24);       // �s�Ԃ��w�肷��
		canvas.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

		ofSetColor(255, 255, 255); // �F���w��
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
		canvas.drawString(text_Q, windowWidth / 2 - text.length() / 2 * fontSize + fontSize * 3,  windowHeight / 2 + fontSize); // �����ƃ|�W�V�������w�肵�ĕ`��

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

	gameState = GAMEOVER;
}

void MainManager::gameClear() {
	gameState = GAMECLEAR;
}

void MainManager::showStatus() {

	int offSet_x = 6;
	int offSet_y = 3;

	//hp�̕\��
	string text = "HP:"+to_string(player->getHp())+"\n"+ "SCORE:" + to_string(player->getScore());
	ofSetColor(255, 255, 255); // �F���w��
	statusBar.drawString(text, windowWidth - offSet_x *fontSize, fontSize); // �����ƃ|�W�V�������w�肵�ĕ`��

}