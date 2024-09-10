#pragma once
#include "stdafx.h"
const int windowWidth = 1024;
const int windowHeight = 768;

const int tileSize = 48;	//1�^�C���̑傫��
const int mapWidth = 16;	//map�̉���
const int mapHeight = 16;   //map�̍���	

//�Q�[���X�e�[�^�X
enum GameState
{
	POSE = 0,
	PLAY = 1,
	GAMEOVER = 2,
	GAMECLEAR = 3
	
};

//�^�O
enum Tag {
	NONE = -1,
	PLAYER = 0,
	ENEMY = 1,
	BLOCK = 2,
	FLAG = 3
};

//�񎟌��x�N�g��
struct float2 {
	float x;
	float y;

	float2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	float2 operator + (const float2 other) const {
		float2 r = { x + other.x, y + other.y};
		return  r;
	}

	friend float2 operator * (const float2& vec2, const float& c) {
		float2 r = { c * vec2.x, c * vec2.y};
		return r;
	}
	friend float2 operator * (const float& c, const float2& vec2) {
		float2 r = { c * vec2.x, c * vec2.y};
		return r;
	}
	friend float2 operator * (const float2& v1, const float2& v2) {
		float2 r = { v1.x * v2.x, v1.y * v2.y};
		return r;
	}
};

//�O�����x�N�g��
struct float3 {
	float x;
	float y;
	float z;

	float3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float3() {
		this->x = 0;
		this->y = 0;
		this->z= 0;
	}

	float3 operator + (const float3& other) const {
		float3 r = { x + other.x, y + other.y, z + other.z };
		return  r;
	}

	friend float3 operator * ( const float3& vec3, const float& c) {
		float3 r = { c * vec3.x, c * vec3.y, c * vec3.z };
		return r;
	}
	friend float3 operator * (const float& c, const float3& vec3) {
		float3 r = { c * vec3.x, c * vec3.y, c * vec3.z };
		return r;
	}

	friend float3 operator * (const float3& v1, const float3& v2) {
		float3 r = { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
		return r;
	}

};


