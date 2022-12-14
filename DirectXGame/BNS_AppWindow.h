#pragma once
#include "BNS_Window.h"
#include "BNS_DeviceContext.h"
#include "Matrix4x4.h"
#include "BNS_UIManager.h"
#include "BNS_Log.h"

class BNS_Cube;
class BNS_Plane;
class BNS_Camera;
class BNS_Mesh;

// displays the main scene; handles the awake,update,end
class BNS_AppWindow : public BNS_Window
{
public:
	BNS_AppWindow();
	~BNS_AppWindow();

	void render();

	// Inherited via BNS_Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;

private:
	SwapChainPtr m_swap_chain;
	BlenderPtr m_blender;
	RenderToTexturePtr m_scene_views[4];

private:
	friend class BNS_Cube;
	friend class BNS_Plane;
	friend class BNS_Camera;
	friend class BNS_Mesh;
};

