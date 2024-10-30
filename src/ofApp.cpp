#include "stdafx.h"


//--------------------------------------------------------------
void ofApp::setup() {


	mainManager = std::make_shared<MainManager>();
	titleManager = std::make_unique<TitleManager>(mainManager);
	selectManager = std::make_unique<SelectManager>(mainManager);
	mainManager->gameState = TITLE;


}
//--------------------------------------------------------------
void ofApp::update(){
	if (mainManager->gameState == PLAY || mainManager->gameState == POSE ||
		mainManager->gameState == GAMECLEAR || mainManager->gameState == GAMEOVER) {
		mainManager->update();

	}
	
	//タイトル
	if (mainManager->gameState == TITLE) {
		titleManager->update();
	}

	//ステージセレクト
	if (mainManager->gameState == STAGESELECT) {
		selectManager->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//背景色の設定
	ofSetColor(0,0, 0); // 色を指定
	ofDrawRectangle(0, 0, windowWidth, windowHeight);

	//ゲームプレイ中
	if (mainManager->gameState == PLAY || mainManager->gameState == POSE ||
		mainManager->gameState == GAMECLEAR || mainManager->gameState == GAMEOVER) {
		mainManager->draw();
	}
	

	//タイトル
	if (mainManager->gameState == TITLE) {
		titleManager->draw();
	}

	//ステージセレクト
	if (mainManager->gameState == STAGESELECT) {
		selectManager->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key) {
		//タイトル
		if (mainManager->gameState == TITLE) {
			titleManager->input(key);
		}
		//セレクト画面
		if (mainManager->gameState == STAGESELECT) {
			selectManager->input(key);
		}
		//ゲームプレイ中
		if (mainManager->gameState == PLAY || mainManager->gameState == POSE ||
			mainManager->gameState == GAMECLEAR || mainManager->gameState == GAMEOVER) {
			mainManager->input(key);
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
