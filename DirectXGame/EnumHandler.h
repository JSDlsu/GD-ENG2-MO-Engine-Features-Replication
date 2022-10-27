#pragma once
#include "Vector2D.h"
#include "Vector3D.h"

struct vertex_tex
{
	Vector3D position;
	Vector2D texcoord;
};

struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

enum class ObjectTypes
{
	CUBE = 0,
	MESH,
	PLANE,
	CAMERA
};

enum class VertexShaderType
{
	DEFAULT = 0,
	MESH
};

enum class PixelShaderType
{
	DEFAULT = 0,
};

class EnumHandler
{
	
};