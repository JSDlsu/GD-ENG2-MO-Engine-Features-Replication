#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

/*
 * blending combines pixel shader colors of incoming pixel
 * data and current pixel data(source and destination).
 * This removes the default of overwriting pixel shader
 * data on the back buffer. Blending has many combinations
 * where it can do alpha blend, addition, and subtraction.
 */
class BNS_Blender
{
public:
	BNS_Blender(BNS_RenderSystem* system);
	~BNS_Blender();
private:
	ID3D11BlendState* pp_blend_state_;
	BNS_RenderSystem* m_system = nullptr;
private:
	friend class BNS_DeviceContext;
};

