#pragma once



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

struct vertex_pos_lerp
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
};

struct vertex_color_lerp
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

struct vertex_pos_color_lerp
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};


struct ShaderByteData
{
	void* m_byte_code[2048];
	size_t m_size;
};

class StructHandler
{
	
};