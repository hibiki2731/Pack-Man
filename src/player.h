
#pragma once
#include "stdafx.h"

class Player :public GameObject
{
	enum Direct {
		IDLE = 0,
		RIGHT = 1,
		LEFT = -1,
		UP = -1,
		DOWN = 1
	};

public:
	//コンストラクタ
	Player(int posIndex[2]);
	Player(int posIndex);


	//更新関数
	void update(char(&blockMap)[mapHeight][mapWidth],char(&objectMap)[mapHeight][mapWidth]) override;	//ゲーム更新
	void draw() override;	//出力更新
	void input(int key);   //入力処理

	float getPos_x() override;
	float getPos_y() override;
	float getRad() override;
	bool hasCollider() override;
	int getPosIndex_x();
	int getPosIndex_y();
	int getcurrentDirect_x();
	int getcurrentDirect_y();

	int getHp();
	int getScore();

	void collisionAct(GameObject* collider);	//衝突時の処理


private:

	float radius;		//プレイヤーの半径

	int mPosIndex[2];	//プレイヤーのindex座標
	int mPrePosIndex[2];	//更新前のインデックス座標
	//描画に用いるプレイヤーの座標
	float x;
	float y;
	//移動の目標座標
	float targetPos_x;
	float targetPos_y;
	//目標座標との許容範囲

	float speed;	//移動の速さ
	Direct nextDirect[2];	//次の向き
	Direct currentDirect[2];	//現在の向き

	void mapView(char (&map)[mapHeight][mapWidth]);	//デバッグ用
	void updateMap(char(&map)[mapHeight][mapWidth]);	//プレイヤーのマップ位置の更新

	//ステータス
	int hp;
	int timeCounter;
	int invincibleLength;
	int score;

	//描画用
	int sliceNum;
	int thickness;

};

