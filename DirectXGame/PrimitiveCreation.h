#pragma once
#include "BNS_Prerequisites.h"
#include "BNS_StructHandler.h"
#include "Vector3D.h"

enum class BNS_VertexShaderType;

class PrimitiveCreation
{
private:
	PrimitiveCreation();
	~PrimitiveCreation();
	PrimitiveCreation(PrimitiveCreation const&) {}; // copy constructor is private
	PrimitiveCreation& operator=(PrimitiveCreation const&) {}; // assignment operator is private

public:
	void ChangeVB_IB_Buffer(BNS_VertexShaderType vs_type, VertexBufferPtr& m_vb, IndexBufferPtr& m_ib, BNS_PC_Cube_ColorData color_data);

private:
	void GetCube_Tex(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib);
	void GetCube_Color(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib, BNS_PC_Cube_ColorData color_data);
	void GetCube_Color_Lerp(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib, BNS_PC_Cube_ColorData color_data);

public:
	static void create();
	static void release();
	static PrimitiveCreation* Instance();

private:
	Vector3D cube_positionList[8];

private:
	static PrimitiveCreation* sharedInstance;
	friend class Cube;
};

