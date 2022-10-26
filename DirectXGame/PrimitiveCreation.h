#pragma once
#include "AppWindow.h"
#include "Prerequisites.h"
#include "Vector2D.h"
#include "Vector3D.h"

struct vertex_tex
{
	Vector3D position;
	Vector2D texcoord;
};

class PrimitiveCreation
{
private:
	PrimitiveCreation();
	~PrimitiveCreation();
	PrimitiveCreation(PrimitiveCreation const&) {}; // copy constructor is private
	PrimitiveCreation& operator=(PrimitiveCreation const&) {}; // assignment operator is private

public:
	void GetCubeWithTexture(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib);

public:
	static void create();
	static void release();
	static PrimitiveCreation* Instance();

private:
	static PrimitiveCreation* sharedInstance;
	friend class Cube;
};

