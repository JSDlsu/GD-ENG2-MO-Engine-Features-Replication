#pragma once
#include "Window.h"
#include "DeviceContext.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "Line.h"


class Cube;
class Plane;
class Camera;
class Mesh;

//FOR OBJECT PICKING
struct PickingRay
{
	Vector3D origin;
	Vector3D direction;
};

// displays the main scene; handles the awake,update,end
class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	void update();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// Inherited via InputListener
	// KEYBOARD; pure virtual callback functions
	void onKeyDown(int key) override;
	void onKeyUp(int key) override;

	// MOUSE; pure virtual callback functions
	void onMouseMove(const Point& mouse_pos) override;

	void onLeftMouseDown(const Point& delta_mouse_pos) override;
	void onLeftMouseUp(const Point& delta_mouse_pos) override;
	void onRightMouseDown(const Point& delta_mouse_pos) override;
	void onRightMouseUp(const Point& delta_mouse_pos) override;

	void Pick(const Point& delta_mouse_pos);

private:
	SwapChainPtr m_swap_chain;
	BlenderPtr m_blender;
private:
	PickingRay ray;
	Line* line1;
private:
	friend class Cube;
	friend class Plane;
	friend class Camera;
	friend class Mesh;
};



