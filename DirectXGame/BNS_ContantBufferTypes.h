#pragma once
#include "Matrix4x4.h"

// constant buffer; this is updated per frame

// constant buffer for object's transform attributes
__declspec(align(16))
struct BNS_constant_transform
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	Vector4D m_light_direction;
	Vector4D m_camera_position;
	Vector4D m_light_position = Vector4D(0,1,0,0);
	float m_light_radius = 4.0f;
	float m_time = 0.0f;
	float alpha = 1.0f;
};
