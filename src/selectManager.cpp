#include "stdafx.h"

SelectManager::SelectManager(std::shared_ptr<MainManager> mainManager) {
	mMainManager = mainManager;

	isSelect = false;

	fontSize_title = 70;
	canvas_title.load("SawarabiMincho-Regular.ttf", fontSize_title); // フォントのデータを指定する
	canvas_title.setLineHeight(24);       // 行間を指定する
	canvas_title.setLetterSpacing(1.0);   // 文字間を指定する

	selectNum = 0;

	panelWidth = windowWidth / 6;
	panelHeight = windowHeight / 8;


}

void SelectManager::update() {
	if (mMainManager->gameState == STAGESELECT && !isSelect) {
		isSelect = true;
	}

	if (mMainManager->gameState != STAGESELECT && isSelect) {
	}

}

void SelectManager::draw() {

	string title = "STAGE SELECT";
	// Fonts
	ofTrueTypeFont::setGlobalDpi(72);

	ofSetColor(255, 255, 0);// 色を指定
	canvas_title.drawString(title, windowWidth / 2 - (title.length() - 2) / 2 * fontSize_title + 10, fontSize_title * 2); // 文字とポジションを指定して描画


	ofVec3f color = palet();
	for (int i = 0; i < 8; i++) {
		if (i == selectNum) ofSetColor(color.x, color.y, color.z);
		else ofSetColor(255, 255, 0);
		if (i < 4) {
			drawPanel(windowWidth / 22 + panelWidth * i * 3 / 2, panelHeight * 3);
		}
		else if(i < 8){
			drawPanel(windowWidth / 22 + panelWidth * (i - 4) * 3 / 2, panelHeight * 4.5);
		}
	}

}

void SelectManager::input(int key) {
	switch (key)
	{
	case OF_KEY_RIGHT:
		selectNum += 1;
		if (selectNum > 7) selectNum = 0;
		break;
	case OF_KEY_LEFT:
		selectNum -= 1;
		if (selectNum < 0) selectNum = 7;
		break;
	case OF_KEY_UP:
		selectNum -= 4;
		if (selectNum < 0) selectNum += 8;

		break;
	case OF_KEY_DOWN:
		selectNum += 4;
		if (selectNum > 7) selectNum -= 8;
		break;
	case OF_KEY_RETURN:
		if (isSelect) {
			moveScene();
		}
		break;

	default:
		break;
	}

}

void SelectManager::drawPanel(int x, int y) {
	ofDrawRectangle(x, y, panelWidth, panelHeight);
}

ofVec3f SelectManager::palet() {

		float t = std::hypot(( windowWidth / 2 + 120) / windowWidth, (windowHeight / 2) / windowHeight) + ofGetElapsedTimef() * 2;
		ofVec3f a;
		ofVec3f b;
		ofVec3f c;
		ofVec3f d;
		ofVec3f e;
		a = { 0.731, 3, 0.53 };
		b = { 0.247, 0.752, 0.453 };
		c = { 0.785, 0.265, 0.241 };
		d = { 0.138, 1.918, 0.837 };
		e = { cosf(2 * PI * (c.x * t + d.x)), 1, cosf(2 * PI * (c.z * t + d.z)) };
		ofVec3f r = a + b * e;

		return r * 255;

}

void SelectManager::moveScene() {
	isSelect = false;
	if (selectNum > 1) return;
	mMainManager->setStageNum(selectNum + 1);
	mMainManager->gameState = PLAY;


	mMainManager->init();

}