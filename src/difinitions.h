#pragma once

const int windowWidth = 1024;
const int windowHeight = 768;

const int tileSize = 48;	//1ƒ^ƒCƒ‹‚Ì‘å‚«‚³
const int mapWidth = 16;	//map‚Ì‰¡•
const int mapHeight = 16;   //map‚Ì‚‚³	

enum GameState
{
	POSE = 0,
	PLAY = 1,
	GAMEOVER = 2,
	GAMECLEAR = 3
	
};
