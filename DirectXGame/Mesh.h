#pragma once
#include "AGameObject.h"
#include "Resource.h"
#include "Prerequisites.h"

class AppWindow;

/*
 *contains the resource and shaderResourceView attributes.
 *The _mesh class requires the ‘tinyobj’ header file in
 *order for it to parse data of the models.
 */
class Mesh : public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();

	const VertexBufferPtr& getVertexBuffer();
	const IndexBufferPtr& getIndexBuffer();
private:
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
private:
	friend class DeviceContext;
};
