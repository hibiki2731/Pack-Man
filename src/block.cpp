#include "stdafx.h"

Block::Block(int posIndex[2]) {
	x = (float)posIndex[0] * tileSize;
	y = (float)posIndex[1] * tileSize;
}
Block::Block(int posIndex) {
	x = (float)(posIndex% mapWidth) * tileSize;
	y = (float)(posIndex/mapWidth) * tileSize;
}

void Block::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum) {

}

void Block::draw() {
	ofSetColor(mColor);
	ofDrawRectangle(x, y, tileSize, tileSize);
}


float Block::getPos_x() {
	return x;
}

float Block::getPos_y() {
	return y;
}
float Block::getRad() {
	throw "this GameObject does not have radius";
}
bool Block::hasCollider() {
	return false;
}



StoneBlock::StoneBlock(int posIndex[2]) : Block(posIndex) {
	mColor = { 100,100,100,255 };
}

StoneBlock::StoneBlock(int posIndex): Block(posIndex) {
	
	mColor = { 100,100,100,255 };
}