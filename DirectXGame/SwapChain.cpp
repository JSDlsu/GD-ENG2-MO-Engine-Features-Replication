#include "SwapChain.h"
#include "RenderSystem.h"
#include <exception>


SwapChain::SwapChain(HWND hwnd, UINT width, UINT height, RenderSystem* system) : m_system(system)
{
	// pointer to DirectX device
	ID3D11Device* device = m_system->m_d3d_device;

	// pointer to SwapChain descriptor
	DXGI_SWAP_CHAIN_DESC desc;
	// 'ZeroMemory' - allows us to fill all the memory occupied by our descriptor with zero
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	// Size of our window W * H
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	// pixel format of our frame buffer; 8 bits for each of the four color channels(RGBA)
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	// we set the buffer's role to 'renderTarget'
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	// enabled window mode
	desc.Windowed = TRUE;

	//Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = m_system->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

	if (FAILED(hr))
	{
		throw std::exception("SwapChain not created successfully");
	}

	//Get the back buffer color and create its render target view
	//--------------------------------
	ID3D11Texture2D* buffer = NULL;
	hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		throw std::exception("SwapChain not created successfully");
	}

	// Create a render-target view for accessing resource data.
	hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
	buffer->Release();

	if (FAILED(hr))
	{
		throw std::exception("SwapChain not created successfully");
	}

}

bool SwapChain::present(bool vsync)
{
	// presents a rendered image to the user
	/* if the syncInterval is zero / false the presentation occurs immediately without
	synchronization, otherwise we have synchronization */
	m_swap_chain->Present(vsync, NULL);

	return true;
}

SwapChain::~SwapChain()
{
	m_rtv->Release();
	m_swap_chain->Release();
}