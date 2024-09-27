#include "stdafx.h"

SelectManager::SelectManager(std::shared_ptr<MainManager> mainManager) {
	mMainManager = mainManager;


	fontSize_title = 50;
	canvas_title.load("SawarabiMincho-Regular.ttf", fontSize_title); // �t�H���g�̃f�[�^���w�肷��
	canvas_title.setLineHeight(24);       // �s�Ԃ��w�肷��
	canvas_title.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

	selectNum = 1;


}

void SelectManager::update() {

}

void SelectManager::draw() {

	string title = "STAGE SELECT";
	int fontSize = 80;
	// Fonts
	ofTrueTypeFont::setGlobalDpi(72);

	ofSetColor(255, 255, 0); // �F���w��
	canvas_title.drawString(title, windowWidth / 2 - (title.length() - 1) / 2 * fontSize + 10, fontSize_title); // �����ƃ|�W�V�������w�肵�ĕ`��

}

void SelectManager::input(int key) {

}
