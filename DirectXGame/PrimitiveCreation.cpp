#include "PrimitiveCreation.h"
#include <iostream>
#include "BNS_AppWindow.h"
#include "BNS_Color.h"
#include "BNS_GraphicsEngine.h"
#include "ShaderEngine.h"

PrimitiveCreation* PrimitiveCreation::sharedInstance = nullptr;

PrimitiveCreation::PrimitiveCreation()
{
	Vector3D cube_position[] =
	{
		//FRONT FACE
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},
		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};
	UINT cube_size = sizeof(cube_position);
	::memcpy(cube_positionList, cube_position, cube_size);
}

PrimitiveCreation::~PrimitiveCreation()
{

}

void PrimitiveCreation::ChangeVB_IB_Buffer(BNS_VertexShaderType vs_type, VertexBufferPtr& m_vb, IndexBufferPtr& m_ib, BNS_PC_Cube_ColorData color_data)
{
	switch (vs_type)
	{
	case BNS_VertexShaderType::TEXTURE:
		GetCube_Tex(m_vb, m_ib);
		break;
	case BNS_VertexShaderType::COLOR:
		GetCube_Color(m_vb, m_ib, color_data);
		break;
	case BNS_VertexShaderType::COLOR_LERP:
		GetCube_Color_Lerp(m_vb, m_ib, color_data);
		break;
	}
}

void PrimitiveCreation::GetCube_Tex(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib)
{

	// UV Coords
	Vector2D texcoord_list[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	// list of all the BNS_vertex_tex in the 3D Cube
	BNS_vertex_tex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ cube_positionList[0],texcoord_list[1] },
		{ cube_positionList[1],texcoord_list[0] },
		{ cube_positionList[2],texcoord_list[2] },
		{ cube_positionList[3],texcoord_list[3] },


		{ cube_positionList[4],texcoord_list[1] },
		{ cube_positionList[5],texcoord_list[0] },
		{ cube_positionList[6],texcoord_list[2] },
		{ cube_positionList[7],texcoord_list[3] },


		{ cube_positionList[1],texcoord_list[1] },
		{ cube_positionList[6],texcoord_list[0] },
		{ cube_positionList[5],texcoord_list[2] },
		{ cube_positionList[2],texcoord_list[3] },

		{ cube_positionList[7],texcoord_list[1] },
		{ cube_positionList[0],texcoord_list[0] },
		{ cube_positionList[3],texcoord_list[2] },
		{ cube_positionList[4],texcoord_list[3] },

		{ cube_positionList[3],texcoord_list[1] },
		{ cube_positionList[2],texcoord_list[0] },
		{ cube_positionList[5],texcoord_list[2] },
		{ cube_positionList[4],texcoord_list[3] },

		{ cube_positionList[7],texcoord_list[1] },
		{ cube_positionList[6],texcoord_list[0] },
		{ cube_positionList[1],texcoord_list[2] },
		{ cube_positionList[0],texcoord_list[3] }


	};

	// list of all the triangle index with their BNS_vertex_tex compositions
	// this index list should reflect the BNS_vertex_tex list
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	UINT size_list = ARRAYSIZE(vertex_list);

	UINT size_index_list = ARRAYSIZE(index_list);

	// create IB
	m_ib = BNS_GraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer
	(index_list, size_index_list);

	// create VB
	m_vb = BNS_GraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(
		vertex_list,
		sizeof(BNS_vertex_tex), size_list,
		BNS_InputLayoutType::TEXTURE);
}

void PrimitiveCreation::GetCube_Color(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib, BNS_PC_Cube_ColorData color_data)
{
	// list of all the BNS_vertex_tex in the 3D Cube
	BNS_vertex_color vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ cube_positionList[0],color_data.color_list_1[1] },
		{ cube_positionList[1],color_data.color_list_1[0] },
		{ cube_positionList[2],color_data.color_list_1[2] },
		{ cube_positionList[3],color_data.color_list_1[3] },

		{ cube_positionList[4],color_data.color_list_1[1] },
		{ cube_positionList[5],color_data.color_list_1[0] },
		{ cube_positionList[6],color_data.color_list_1[2] },
		{ cube_positionList[7],color_data.color_list_1[3] },

		{ cube_positionList[1],color_data.color_list_1[1] },
		{ cube_positionList[6],color_data.color_list_1[0] },
		{ cube_positionList[5],color_data.color_list_1[2] },
		{ cube_positionList[2],color_data.color_list_1[3] },

		{ cube_positionList[7],color_data.color_list_1[1] },
		{ cube_positionList[0],color_data.color_list_1[0] },
		{ cube_positionList[3],color_data.color_list_1[2] },
		{ cube_positionList[4],color_data.color_list_1[3] },

		{ cube_positionList[3],color_data.color_list_1[1] },
		{ cube_positionList[2],color_data.color_list_1[0] },
		{ cube_positionList[5],color_data.color_list_1[2] },
		{ cube_positionList[4],color_data.color_list_1[3] },

		{ cube_positionList[7],color_data.color_list_1[1] },
		{ cube_positionList[6],color_data.color_list_1[0] },
		{ cube_positionList[1],color_data.color_list_1[2] },
		{ cube_positionList[0],color_data.color_list_1[3] }


	};

	// list of all the triangle index with their BNS_vertex_tex compositions
	// this index list should reflect the BNS_vertex_tex list
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	UINT size_list = ARRAYSIZE(vertex_list);

	UINT size_index_list = ARRAYSIZE(index_list);

	// create IB
	m_ib = BNS_GraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer
	(index_list, size_index_list);
	

	// create VB
	m_vb = BNS_GraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(
		vertex_list,
		sizeof(BNS_vertex_color), size_list,
		BNS_InputLayoutType::COLOR);
}

void PrimitiveCreation::GetCube_Color_Lerp(VertexBufferPtr& m_vb, IndexBufferPtr& m_ib, BNS_PC_Cube_ColorData color_data)
{
	// list of all the BNS_vertex_tex in the 3D Cube
	BNS_vertex_color_lerp vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{ cube_positionList[0],color_data.color_list_1[1], color_data.color_list_2[1] },
		{ cube_positionList[1],color_data.color_list_1[0], color_data.color_list_2[0] },
		{ cube_positionList[2],color_data.color_list_1[2], color_data.color_list_2[2] },
		{ cube_positionList[3],color_data.color_list_1[3], color_data.color_list_2[3] },

		{ cube_positionList[4],color_data.color_list_1[1], color_data.color_list_2[1] },
		{ cube_positionList[5],color_data.color_list_1[0], color_data.color_list_2[0] },
		{ cube_positionList[6],color_data.color_list_1[2], color_data.color_list_2[2] },
		{ cube_positionList[7],color_data.color_list_1[3], color_data.color_list_2[3] },

		{ cube_positionList[1],color_data.color_list_1[1], color_data.color_list_2[1] },
		{ cube_positionList[6],color_data.color_list_1[0], color_data.color_list_2[0] },
		{ cube_positionList[5],color_data.color_list_1[2], color_data.color_list_2[2] },
		{ cube_positionList[2],color_data.color_list_1[3], color_data.color_list_2[3] },

		{ cube_positionList[7],color_data.color_list_1[1], color_data.color_list_2[1] },
		{ cube_positionList[0],color_data.color_list_1[0], color_data.color_list_2[0] },
		{ cube_positionList[3],color_data.color_list_1[2], color_data.color_list_2[2] },
		{ cube_positionList[4],color_data.color_list_1[3], color_data.color_list_2[3] },

		{ cube_positionList[3],color_data.color_list_1[1], color_data.color_list_2[1] },
		{ cube_positionList[2],color_data.color_list_1[0], color_data.color_list_2[0] },
		{ cube_positionList[5],color_data.color_list_1[2], color_data.color_list_2[2] },
		{ cube_positionList[4],color_data.color_list_1[3], color_data.color_list_2[3] },

		{ cube_positionList[7],color_data.color_list_1[1], color_data.color_list_2[1] },
		{ cube_positionList[6],color_data.color_list_1[0], color_data.color_list_2[0] },
		{ cube_positionList[1],color_data.color_list_1[2], color_data.color_list_2[2] },
		{ cube_positionList[0],color_data.color_list_1[3], color_data.color_list_2[3] }
	};

	// list of all the triangle index with their BNS_vertex_tex compositions
	// this index list should reflect the BNS_vertex_tex list
	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	UINT size_list = ARRAYSIZE(vertex_list);

	UINT size_index_list = ARRAYSIZE(index_list);

	// create IB
	m_ib = BNS_GraphicsEngine::get()->getRenderSystem()->CreateIndexBuffer
	(index_list, size_index_list);

	// create VB
	m_vb = BNS_GraphicsEngine::get()->getRenderSystem()->CreateVertexBuffer(
		vertex_list,
		sizeof(BNS_vertex_color_lerp), size_list,
		BNS_InputLayoutType::COLOR_LERP);
}


void PrimitiveCreation::create()
{
	if (PrimitiveCreation::sharedInstance)
		throw std::exception("PrimitiveCreation already created");
	else
	{
		PrimitiveCreation::sharedInstance = new PrimitiveCreation();
	}
}

void PrimitiveCreation::release()
{
	if (!PrimitiveCreation::sharedInstance)
		return;
	delete PrimitiveCreation::sharedInstance;
}

PrimitiveCreation* PrimitiveCreation::Instance()
{
	return sharedInstance;
}
