#pragma once
#include "BNS_InputListener.h"
#include <unordered_set>

#include "BNS_AppWindow.h"
#include "Point.h"

// manages all the various input devices in mouse, keyboard, etc...
class BNS_InputSystem
{
private:
	BNS_InputSystem();
	~BNS_InputSystem();
public:
	void update(HWND& hwnd);
	void addListener(BNS_InputListener* listener);
	void removeListener(BNS_InputListener* listener);
	void setCursorPosition(const Point& pos);
	void showCursor(bool show);
public:
	static BNS_InputSystem* get();
	static void create();
	static void release();
private:
	std::unordered_set<BNS_InputListener*> m_set_listeners;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point m_old_mouse_pos;
	bool m_first_time = true;
	static BNS_InputSystem* m_system;
};