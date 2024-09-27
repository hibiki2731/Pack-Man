#pragma once
#include "stdafx.h"

class TitleManager {
public:
	TitleManager(std::shared_ptr<MainManager> mainManager);

	void update();
	void draw();
	void input(int key);

	void stopBGM();

private:
	std::shared_ptr<MainManager> mMainManager;

	ofSoundPlayer titleBGM;

	ofTrueTypeFont canvas;
	int fontSize;
};
