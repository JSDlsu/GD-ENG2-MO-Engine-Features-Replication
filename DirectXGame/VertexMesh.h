#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

/*
 * a class structure that will contain the Vector3
 * vertex_tex and Vector2 tex-coordinates of each point.
 */
class VertexMesh
{
public:
	// default constructor
	VertexMesh() :m_position(), m_texcoord()
	{
	}
	// modified valued vector
	VertexMesh(Vector3D position, Vector2D texcoord) :m_position(position), m_texcoord(texcoord)
	{
	}
	// deep-copy of values
	VertexMesh(const VertexMesh& vertex) :m_position(vertex.m_position), m_texcoord(vertex.m_texcoord)
	{
	}

	~VertexMesh()
	{
	}

public:
	// representation of the _mesh structure attribute
	Vector3D m_position;
	Vector2D m_texcoord;
};