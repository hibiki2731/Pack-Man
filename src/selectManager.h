#pragma once
#include "stdafx.h"

class SelectManager {
public:
	SelectManager();

	void update();
	void draw();
	void input();

private:

	std::shared_ptr<MainManager> mMainManager;

};