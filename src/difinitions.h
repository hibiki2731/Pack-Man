#pragma once

const int windowWidth = 1024;
const int windowHeight = 768;

const int tileSize = 48;	//1�^�C���̑傫��
const int mapWidth = 16;	//map�̉���
const int mapHeight = 16;   //map�̍���	

enum GameState
{
	POSE = 0,
	PLAY = 1,
	GAMEOVER = 2,
	GAMECLEAR = 3
	
};
