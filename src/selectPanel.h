#pragma once
class SelectPanel
{
public:
	SelectPanel();

	void update();
	void draw();
	void input(int key);


private:
	bool isActive;
};

