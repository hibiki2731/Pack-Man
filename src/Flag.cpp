#include "stdafx.h"

Flag::Flag(int posIndex) {


	x = (float)((posIndex % mapWidth) * tileSize + tileSize / 2);
	y = (float)((posIndex / mapWidth) * tileSize + tileSize / 2);
	radius = tileSize / 8;

	sliceNumX = 6;
	sliceNumY = 7;
	tag = FLAG;
}

void Flag::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth]) {

}

void Flag::draw() {

	//ƒtƒ‰ƒO‚Ì•`‰æ
	float3 flagCol = palette(x, y);
	ofSetColor(ofColor(flagCol.x, flagCol.y, flagCol.z, 255));
	ofDrawCircle(x, y, radius);
	/*
	for (int i = 0; i < sliceNumX; i++) {
		float3 flagCol = palette((x + radius * cos(2 * PI / sliceNumX * (i + 1 / 2))), (y + radius * sin(2 * PI / sliceNumX * (i + 1 / 2))));
		ofSetColor(ofColor(flagCol.x, flagCol.y, flagCol.z, 255));
		for (int t = 0; t < sliceNumY; t++) {
			float r = radius / sliceNumY * t;
			ofDrawLine(x + r * cos(2 * PI / sliceNumX * i), y + r * sin(2 * PI / sliceNumX * i), x + r * cos(2 * PI / sliceNumX * (i + 1)), y + r * sin(2 * PI / sliceNumX * (i + 1)));
		}
	}
	*/
}

void Flag::input(int key) {

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