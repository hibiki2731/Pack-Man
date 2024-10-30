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
	
	//�^�C�g��
	if (mainManager->gameState == TITLE) {
		titleManager->update();
	}

	//�X�e�[�W�Z���N�g
	if (mainManager->gameState == STAGESELECT) {
		selectManager->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//�w�i�F�̐ݒ�
	ofSetColor(0,0, 0); // �F���w��
	ofDrawRectangle(0, 0, windowWidth, windowHeight);

	//�Q�[���v���C��
	if (mainManager->gameState == PLAY || mainManager->gameState == POSE ||
		mainManager->gameState == GAMECLEAR || mainManager->gameState == GAMEOVER) {
		mainManager->draw();
	}
	

	//�^�C�g��
	if (mainManager->gameState == TITLE) {
		titleManager->draw();
	}

	//�X�e�[�W�Z���N�g
	if (mainManager->gameState == STAGESELECT) {
		selectManager->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key) {
		//�^�C�g��
		if (mainManager->gameState == TITLE) {
			titleManager->input(key);
		}
		//�Z���N�g���
		if (mainManager->gameState == STAGESELECT) {
			selectManager->input(key);
		}
		//�Q�[���v���C��
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
