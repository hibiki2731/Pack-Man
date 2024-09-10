#include "stdafx.h"

Block::Block(int posIndex[2]) {
	x = (float)posIndex[0] * tileSize;
	y = (float)posIndex[1] * tileSize;

	sliceNum = 2;
	tag = BLOCK;
}
Block::Block(int posIndex) {
	x = (float)(posIndex % mapWidth) * tileSize;
	y = (float)(posIndex / mapWidth) * tileSize;

	sliceNum = 5;
	tag = BLOCK;
}

void Block::update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth], int keyNum) {

}

void Block::draw() {

	for (int i = 0; i < sliceNum; i++) {
		//¶•Ó
		float3 blockCol = palette(x, y + tileSize / sliceNum * (i + 1 / 2));
		ofSetColor(ofColor(blockCol.x, blockCol.y, blockCol.z, 255));
		ofDrawLine(x, y + tileSize / sliceNum * i, x, y + tileSize / sliceNum * (i + 1));

		//‰E•Ó
		blockCol = palette(x + tileSize, y + tileSize / sliceNum * (i + 1 / 2));
		ofSetColor(ofColor(blockCol.x, blockCol.y, blockCol.z, 255));
		ofDrawLine(x + tileSize, y + tileSize / sliceNum * i, x + tileSize, y + tileSize / sliceNum * (i + 1));

		//ã•Ó
		blockCol = palette(x + tileSize / sliceNum * (i + 1 / 2), y);
		ofSetColor(ofColor(blockCol.x, blockCol.y, blockCol.z, 255));
		ofDrawLine(x + tileSize / sliceNum * i, y, x + tileSize / sliceNum * (i + 1), y);

		//‰º•Ó
		blockCol = palette(x + tileSize / sliceNum * (i + 1 / 2), y + tileSize);
		ofSetColor(ofColor(blockCol.x, blockCol.y, blockCol.z, 255));
		ofDrawLine(x + tileSize / sliceNum * i, y + tileSize, x + tileSize / sliceNum * (i + 1), y + tileSize);
	}

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

StoneBlock::StoneBlock(int posIndex) : Block(posIndex) {

	mColor = { 100,100,100,255 };
}