#include "stdafx.h"

Flag::Flag(int posIndex) {


	x = (float)((posIndex % mapWidth) * tileSize + tileSize / 2);
	y = (float)((posIndex / mapWidth) * tileSize + tileSize / 2);
	radius = tileSize / 4;
}

void Flag::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum) {

}

void Flag::draw() {

	//ÉvÉåÉCÉÑÅ[ÇÃï`âÊ
	ofSetColor(ofColor(255, 255, 0, 255));
	ofDrawCircle(x, y, radius);
}

float Flag::getPos_x() {
	return x;
}
float Flag::getPos_y() {
	return y;
}
float Flag::getRad() {
	return radius;
}

bool Flag::hasCollider() {
	return true;
}