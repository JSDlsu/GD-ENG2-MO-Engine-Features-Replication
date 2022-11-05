#pragma once
#include "Window.h"
#include "DeviceContext.h"
#include "Matrix4x4.h"
#include "UIManager.h"	

class Cube;
class Plane;
class BNS_Camera;
class BNS_Mesh;

// displays the main scene; handles the awake,update,end
class BNS_AppWindow : public Window
{
public:
	BNS_AppWindow();
	~BNS_AppWindow();

	void update();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

private:
	SwapChainPtr m_swap_chain;
	BlenderPtr m_blender;
private:
private:
	friend class Cube;
	friend class Plane;
	friend class BNS_Camera;
	friend class BNS_Mesh;
};

