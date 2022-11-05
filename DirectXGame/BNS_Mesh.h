#pragma once
#include "BNS_AGameObject.h"
#include "BNS_Resource.h"
#include "BNS_Prerequisites.h"

class BNS_AppWindow;

/*
 *contains the resource and shaderResourceView attributes.
 *The _mesh class requires the ‘tinyobj’ header file in
 *order for it to parse data of the models.
 */
class BNS_Mesh : public BNS_Resource
{
public:
	BNS_Mesh(const wchar_t* full_path);
	~BNS_Mesh();

	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();
private:
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
private:
	friend class BNS_DeviceContext;
};
