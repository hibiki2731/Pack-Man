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
	//背景色の設定
	ofSetColor(0,0, 0); // 色を指定
	ofDrawRectangle(0, 0, windowWidth, windowHeight);

	mainManager->draw();

	if (mainManager->gameState == POSE) {
		ofTrueTypeFont canvas;
		string text = "POSE";
		int fontSize = 80;
		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
		canvas.setLineHeight(24);       // 行間を指定する
		canvas.setLetterSpacing(1.0);   // 文字間を指定する

		ofSetColor(255, 255, 255); // 色を指定
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
	}

	if (mainManager->gameState == GAMEOVER) {
		ofTrueTypeFont canvas;
		string text = "GAMEOVER";
		int fontSize = 80;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
		canvas.setLineHeight(24);       // 行間を指定する
		canvas.setLetterSpacing(1.0);   // 文字間を指定する

		ofSetColor(255, 50, 50); // 色を指定
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
	}

	if(mainManager->gameState == GAMECLEAR){
		ofTrueTypeFont canvas;
		string text = "CONGRATULATION!!";
		int fontSize = 30;

		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
		canvas.setLineHeight(24);       // 行間を指定する
		canvas.setLetterSpacing(1.0);   // 文字間を指定する

		ofSetColor(255, 255, 255); // 色を指定
		canvas.drawString(text, windowWidth / 2 - text.length() / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
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
