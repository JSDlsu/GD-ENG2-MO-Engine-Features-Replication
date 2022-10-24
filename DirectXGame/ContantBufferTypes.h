#pragma once
#include "Matrix4x4.h"

// constant buffer; this is updated per frame

// constant buffer for object's transform attributes
__declspec(align(16))
struct constant_transform
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	unsigned int m_time;
};

// constant buffer for object's texture attributes
__declspec(align(16))
struct constant_texture
{
	float alpha = 1.0f;
	unsigned int  object_type = 0;
};