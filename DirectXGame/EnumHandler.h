#pragma once

enum class ObjectTypes
{
	CUBE = 0,
	MESH,
	PLANE,
	CAMERA,
	LINE,
};

enum class VertexShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP
};

enum class PixelShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP
};

enum class InputLayoutType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP
};

class EnumHandler
{
	
};