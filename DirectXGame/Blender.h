#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

/*
 * blending combines pixel shader colors of incoming pixel
 * data and current pixel data(source and destination).
 * This removes the default of overwriting pixel shader
 * data on the back buffer. Blending has many combinations
 * where it can do alpha blend, addition, and subtraction.
 */
class Blender
{
public:
	Blender(RenderSystem* system);
	~Blender();
private:
	ID3D11BlendState* pp_blend_state_;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};

