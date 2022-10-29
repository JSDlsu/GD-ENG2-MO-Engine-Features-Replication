#pragma once
#include "Vector3D.h"

class Color
{
public:
	static Vector3D Black;
	static Vector3D White;
	static Vector3D Red;
	static Vector3D Blue;
	static Vector3D Yellow;
	static Vector3D Gray;
	static Vector3D Green;
	static Vector3D Purple;
};

Vector3D Color::Black = { 0,0,0 };
Vector3D Color::White = { 1,1,1 };
Vector3D Color::Red = { 1,0,0 };
Vector3D Color::Blue = { 0,0,1 };
Vector3D Color::Yellow = { 1,1,0 };
Vector3D Color::Gray = { 128/255.0f,128 / 255.0f,128 / 255.0f };
Vector3D Color::Green = { 0,128 / 255.0f,0 };
Vector3D Color::Purple = { 128 / 255.0f,0,128 / 255.0f };