#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

// a double buffer screen that draws simultaneously the image/frame scene
class BNS_SwapChain
{
public:
	//Initialize BNS_SwapChain for a window
	BNS_SwapChain(HWND hwnd, UINT width, UINT height, BNS_RenderSystem* system);

	void setFullScreen(bool fullscreen, unsigned int width, unsigned int height);
	void resize(unsigned int width, unsigned int height);
	bool present(bool vsync);
	~BNS_SwapChain();
private:
	void reloadBuffers(unsigned int width, unsigned int height);
private:
	IDXGISwapChain* m_swap_chain = nullptr;
	ID3D11RenderTargetView* m_rtv = nullptr;
	ID3D11DepthStencilView* m_dsv = nullptr;
	BNS_RenderSystem* m_system = nullptr;
private:
	friend class BNS_DeviceContext;
};
