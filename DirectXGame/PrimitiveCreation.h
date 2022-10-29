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
	void GetCube_Tex(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib);
	void GetCube_Color(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib);
	void GetCube_Pos_Lerp(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib);
	void GetCube_Color_Lerp(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib);
	void GetCube_PosColor_Lerp(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib);

public:
	static void create();
	static void release();
	static PrimitiveCreation* Instance();

private:
	static PrimitiveCreation* sharedInstance;
	friend class Cube;
};

