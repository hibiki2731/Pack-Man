#pragma once
#include "stdafx.h"

class SelectManager {
public:
	SelectManager(std::shared_ptr<MainManager> mainManager);

	void update();
	void draw();
	void input(int key);

private:

	std::shared_ptr<MainManager> mMainManager;
	
	ofTrueTypeFont canvas_title;
	int fontSize_title;

	int selectNum;

};