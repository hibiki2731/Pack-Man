#pragma once
#include "stdafx.h"
class Flag :
    public GameObject
{
public:
    Flag(int posIndex);

    void update(char(&blockMap)[mapHeight][mapWidth], char(&objectMap)[mapHeight][mapWidth]) override;
    void draw() override;
    void input(int key) override;
    float getPos_x();
    float getPos_y();
    float getRad();
    bool hasCollider();

private:
    float x;
    float y;
    float radius;

    //F‚Ìˆ—
    int sliceNumX;
    int sliceNumY;
};

