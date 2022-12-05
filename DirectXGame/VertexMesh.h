#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

/*
 * a class structure that will contain the Vector3
 * BNS_vertex_tex and Vector2 tex-coordinates of each point.
 */
class VertexMesh
{
public:
	// default constructor
	VertexMesh() :m_position(), m_texcoord(), m_normal()
	{
	}
	// modified valued vector
	VertexMesh(Vector3D position, Vector2D texcoord, Vector3D normal) :
	m_position(position),
	m_texcoord(texcoord),
	m_normal(normal)
	{
	}
	// deep-copy of values
	VertexMesh(const VertexMesh& vertex) :
	m_position(vertex.m_position),
	m_texcoord(vertex.m_texcoord),
	m_normal(vertex.m_normal)
	{
	}

	~VertexMesh()
	{
	}

public:
	// representation of the _mesh structure attribute
	Vector3D m_position;
	Vector2D m_texcoord;
	Vector3D m_normal;
};