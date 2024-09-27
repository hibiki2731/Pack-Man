#include "stdafx.h"

SelectManager::SelectManager(std::shared_ptr<MainManager> mainManager) {
	mMainManager = mainManager;


	fontSize_title = 50;
	canvas_title.load("SawarabiMincho-Regular.ttf", fontSize_title); // フォントのデータを指定する
	canvas_title.setLineHeight(24);       // 行間を指定する
	canvas_title.setLetterSpacing(1.0);   // 文字間を指定する

	selectNum = 1;


}

void SelectManager::update() {

}

void SelectManager::draw() {

	string title = "STAGE SELECT";
	int fontSize = 80;
	// Fonts
	ofTrueTypeFont::setGlobalDpi(72);

	ofSetColor(255, 255, 0); // 色を指定
	canvas_title.drawString(title, windowWidth / 2 - (title.length() - 1) / 2 * fontSize + 10, fontSize_title); // 文字とポジションを指定して描画

}

void SelectManager::input(int key) {

}
