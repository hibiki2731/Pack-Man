#include "stdafx.h"


//--------------------------------------------------------------
void ofApp::setup() {
	mainManager = new MainManager();
	mainManager->gameState = TITLE;
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

	if (mainManager->gameState == PLAY) {
		mainManager->draw();
	}

	//タイトル
	if (mainManager->gameState == TITLE) {
		ofSetColor(0, 30, 50); // 色を指定
		ofDrawRectangle(0, 0, windowWidth, windowHeight);


		ofSetColor(0, 0, 0); // 色を指定
		ofTrueTypeFont canvas;
		string text = "PRESS ANY KEY";
		string text_Start = "TO START";
		int fontSize = 80;
		// Fonts
		ofTrueTypeFont::setGlobalDpi(72);

		canvas.load("SawarabiMincho-Regular.ttf", fontSize); // フォントのデータを指定する
		canvas.setLineHeight(72);       // 行間を指定する
		canvas.setLetterSpacing(1.0);   // 文字間を指定する

		ofSetColor(255, 255, 255); // 色を指定
		canvas.drawString(text, windowWidth / 2 - (text.length() - 2) / 2 * fontSize, windowHeight / 2); // 文字とポジションを指定して描画
		canvas.drawString(text_Start, windowWidth / 2 - (text_Start.length() - 2) / 2 * fontSize, windowHeight / 2 + fontSize); // 文字とポジションを指定して描画

	}

	//ポーズ中の処理
	if (mainManager->gameState == POSE) {
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

	//ゲームクリア時の処理
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
	case 'r':
		if (mainManager->gameState == POSE) {
			mainManager->exit();
			mainManager->init();
			mainManager->gameState = PLAY;
		}
		break;
	case 'q':
		if (mainManager->gameState == POSE) {
			mainManager->exit();
			mainManager->gameState = TITLE;
		}
		break;
	default:
		if (mainManager->gameState == TITLE) {
			mainManager->gameState = PLAY;
			mainManager->init();
		}
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
