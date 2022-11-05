#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

// constant buffer is a block of data which can store different kinds of data types.
// In the case of game engine, this is use to share data with the shaders(i.e. changing world view projection matrix).
// C++ application can communicate with the shader and update the values in the constant buffers the shader uses.
class BNS_ConstantBuffer
{
public:
	BNS_ConstantBuffer(void* buffer, UINT size_buffer, BNS_RenderSystem* system);
	void update(DeviceContextPtr context, void* buffer);
	~BNS_ConstantBuffer();
private:
	ID3D11Buffer* m_buffer;
	BNS_RenderSystem* m_system = nullptr;
private:
	friend class BNS_DeviceContext;
};