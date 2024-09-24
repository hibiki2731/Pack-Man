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

	ofSetColor(0, 30, 50); // 色を指定
	ofDrawRectangle(0, 0, windowWidth, windowHeight);


	ofTrueTypeFont canvas;
	string title = "PACK MANNNN";
	string text = "PRESS ANY KEY";
	string text_Start = "TO START";
	int fontSize = 80;
	// Fonts
	ofTrueTypeFont::setGlobalDpi(72);

	canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
	canvas.setLineHeight(72);       // 行間を指定する
	canvas.setLetterSpacing(1.0);   // 文字間を指定する

	ofSetColor(255, 255, 0); // 色を指定
	canvas.drawString(title, windowWidth / 2 - (title.length() - 1) / 2 * fontSize + 10, windowHeight / 4); // 文字とポジションを指定して描画
	ofSetColor(255, 255, 255); // 色を指定
	canvas.drawString(text, windowWidth / 2 - (text.length() - 2) / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
	canvas.drawString(text_Start, windowWidth / 2 - (text_Start.length() - 2) / 2 * fontSize, windowHeight / 2 + fontSize); // 文字とポジションを指定して描画
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