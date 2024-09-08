#pragma once

const int windowWidth = 1024;
const int windowHeight = 768;

const int tileSize = 48;	//1タイルの大きさ
const int mapWidth = 16;	//mapの横幅
const int mapHeight = 16;   //mapの高さ	

enum GameState
{
	POSE = 0,
	PLAY = 1,
	GAMEOVER = 2,
	GAMECLEAR = 3
	
};
