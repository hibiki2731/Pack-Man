#include "stdafx.h"



float3 GameObject::palette(float x, float y) {
	float t = std::hypot((x - windowWidth / 2 + 120) / windowWidth, (y - windowHeight / 2) / windowHeight) + ofGetElapsedTimef() / 5;
	float3 a;
	float3 b;
	float3 c;
	float3 d;
	float3 e;
	a = { 0.731, 3, 0.53 };
	b = { 0.247, 0.752, 0.453 };
	c = { 0.785, 0.265, 0.241 };
	d = { 0.138, 1.918, 0.837 };
	e = { cosf(2 * PI * (c.x * t + d.x)), 1, cosf(2 * PI * (c.z * t + d.z)) };
	float3 r = a + b * e;

	return r * 255;
	
}

float3 GameObject::palette(float x, float y, float3 a, float3 b, float3 c, float3 d) {
	float t = std::hypot((x - windowWidth / 2 + 120) / windowWidth, (y - windowHeight / 2) / windowHeight) + ofGetElapsedTimef() / 5;
	float3 e;
	e = { cosf(2 * PI * (c.x * t + d.x)), 1, cosf(2 * PI * (c.z * t + d.z)) };
	float3 r = a + b * e;

	return r * 255;

}