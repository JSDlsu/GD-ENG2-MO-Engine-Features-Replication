#ifndef STRUCT_HANDLER_H
#define STRUCT_HANDLER_H
#include "Color.h"
#include "Vector2D.h"

struct vertex_tex
{
	Vector3D position;
	Vector2D texcoord;
};

struct vertex_color
{
	Vector3D position;
	Vector3D color;
};

struct vertex_color_lerp
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

struct ShaderByteData
{
	void* m_byte_code[2048];
	size_t m_size;
};

struct PC_Cube_ColorData
{
	PC_Cube_ColorData() : is_CL1_initialized(false), is_CL2_initialized(false)
	{
		Vector3D color_temp[8] =
		{
			//FRONT FACE
			Color::White,
			Color::White,
			Color::White,
			Color::White,
			//BACK FACE
			Color::White,
			Color::White,
			Color::White,
			Color::White
		};
		memcpy(color_list_1, color_temp, sizeof(color_temp));
		memcpy(color_list_2, color_temp, sizeof(color_temp));
	}
	Vector3D color_list_1[8];
	bool is_CL1_initialized;
	Vector3D color_list_2[8];
	bool is_CL2_initialized;
};
class StructHandler
{
	
};

#endif
