#include "stdafx.h"

TitleManager::TitleManager(std::shared_ptr<MainManager> mainManager){
	mMainManager = mainManager;
	isTitle = false;

	titleBGM.loadSound("MusMus-PKPK-001.mp3");
	titleBGM.setLoop(true);
	titleBGM.setMultiPlay(true);
	titleBGM.setVolume(0.05);
}

void TitleManager::update() {
	if (mMainManager->gameState == TITLE && !isTitle) {
		isTitle = true;
		titleBGM.play();
	}

	if (mMainManager->gameState != TITLE && isTitle) {
		isTitle = false;
		titleBGM.stop();
	}

}

void TitleManager::draw() {

	ofSetColor(0, 30, 50); // �F���w��
	ofDrawRectangle(0, 0, windowWidth, windowHeight);


	ofTrueTypeFont canvas;
	string title = "PACK MANNNN";
	string text = "PRESS ANY KEY";
	string text_Start = "TO START";
	int fontSize = 80;
	// Fonts
	ofTrueTypeFont::setGlobalDpi(72);

	canvas.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
	canvas.setLineHeight(72);       // �s�Ԃ��w�肷��
	canvas.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

	ofSetColor(255, 255, 0); // �F���w��
	canvas.drawString(title, windowWidth / 2 - (title.length() - 1) / 2 * fontSize + 10, windowHeight / 4); // �����ƃ|�W�V�������w�肵�ĕ`��
	ofSetColor(255, 255, 255); // �F���w��
	canvas.drawString(text, windowWidth / 2 - (text.length() - 2) / 2 * fontSize, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
	canvas.drawString(text_Start, windowWidth / 2 - (text_Start.length() - 2) / 2 * fontSize, windowHeight / 2 + fontSize); // �����ƃ|�W�V�������w�肵�ĕ`��
}

void TitleManager::input(int key) {
	if (key) {
		mMainManager->gameState = PLAY;
		mMainManager->init();
	}
}

void TitleManager::stopBGM() {
	isTitle = false;
	titleBGM.stop();
}