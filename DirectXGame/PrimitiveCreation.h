#pragma once
#include "Prerequisites.h"

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

