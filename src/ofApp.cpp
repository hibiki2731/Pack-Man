#include "stdafx.h"


//--------------------------------------------------------------
void ofApp::setup() {
	mainManager = new MainManager();

}
//--------------------------------------------------------------
void ofApp::update(){
	if (mainManager->gameState == PLAY) {
		mainManager->update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	//�w�i�F�̐ݒ�
	ofSetColor(0,0, 0); // �F���w��
	ofDrawRectangle(0, 0, windowWidth, windowHeight);

	mainManager->draw();

	if (mainManager->gameState == POSE) {
		ofTrueTypeFont canvas;
		string text = "POSE";
		int fontSize = 80;
		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
		canvas.setLineHeight(24);       // �s�Ԃ��w�肷��
		canvas.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

		ofSetColor(255, 255, 255); // �F���w��
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
	}

	if (mainManager->gameState == GAMEOVER) {
		ofTrueTypeFont canvas;
		string text = "GAMEOVER";
		int fontSize = 80;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
		canvas.setLineHeight(24);       // �s�Ԃ��w�肷��
		canvas.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

		ofSetColor(255, 50, 50); // �F���w��
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
	}

	if(mainManager->gameState == GAMECLEAR){
		ofTrueTypeFont canvas;
		string text = "CONGRATULATION!!";
		int fontSize = 30;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // �t�H���g�̃f�[�^���w�肷��
		canvas.setLineHeight(24);       // �s�Ԃ��w�肷��
		canvas.setLetterSpacing(1.0);   // �����Ԃ��w�肷��

		ofSetColor(255, 255, 255); // �F���w��
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // �����ƃ|�W�V�������w�肵�ĕ`��
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	mainManager->setKey(key);
	switch (key) {
	case 'p':
		if (mainManager->gameState == PLAY) {
			mainManager->gameState = POSE;

		}
		else if (mainManager->gameState == POSE) {
			mainManager->gameState = PLAY;
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
