#pragma once
#include "Vector2D.h"
#include "Vector3D.h"

enum class ObjectTypes
{
	CUBE = 0,
	MESH,
	PLANE,
	CAMERA
};

enum class VertexShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	POS_LERP,
	COLOR_LERP,
	POS_COLOR_LERP
};

enum class PixelShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	POS_LERP,
	COLOR_LERP,
	POS_COLOR_LERP
};

class EnumHandler
{
	
};