#include "BNS_InputSystem.h"

#include <iostream>
#include <Windows.h>

BNS_InputSystem* BNS_InputSystem::m_system = nullptr;

BNS_InputSystem::BNS_InputSystem()
{
}


BNS_InputSystem::~BNS_InputSystem()
{
	BNS_InputSystem::m_system = nullptr;
}

void BNS_InputSystem::update(HWND& hwnd)
{
	// gets the recent
	POINT current_mouse_pos = {};
	::GetCursorPos(&current_mouse_pos);
	//ScreenToClient(hwnd, &current_mouse_pos);
	//std::cout << "X: " << current_mouse_pos.x << "Y: " << current_mouse_pos.y << std::endl;

	// assigns the first current_mouse_pos to the old_mouse_pos
	if (m_first_time)
	{
		m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);
		m_first_time = false;
	}

	// check if there is a difference in the old_mouse_pos to the current_mouse_pos
	if (current_mouse_pos.x != m_old_mouse_pos.m_x || current_mouse_pos.y != m_old_mouse_pos.m_y)
	{
		// There is a MOUSE EVENT
		std::unordered_set<BNS_InputListener*>::iterator it = m_set_listeners.begin();

		while (it != m_set_listeners.end())
		{
			(*it)->onMouseMove(Point(current_mouse_pos.x, current_mouse_pos.y));
			++it;
		}
	}
	// update our old_mouse_pos
	m_old_mouse_pos = Point(current_mouse_pos.x, current_mouse_pos.y);

	// check if there is an active state in our keys
	if (::GetKeyboardState(m_keys_state))
	{
		// iterate all the keys from our keyboard
		for (unsigned int i = 0; i < 256; i++)
		{
			// KEY IS DOWN
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<BNS_InputListener*>::iterator it = m_set_listeners.begin();

				while (it != m_set_listeners.end())
				{
					// if left mouse button is clicked
					if (i == VK_LBUTTON)
					{
						// call event
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onLeftMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					// if right mouse button is clicked
					else if (i == VK_RBUTTON)
					{
						// call event
						if (m_keys_state[i] != m_old_keys_state[i])
							(*it)->onRightMouseDown(Point(current_mouse_pos.x, current_mouse_pos.y));
					}
					else
					{
						// call event
						(*it)->onKeyDown(i);
					}
					++it;
				}
			}
			else // KEY IS UP
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<BNS_InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						// if left mouse button is released
						if (i == VK_LBUTTON)
						{
							// call event
							(*it)->onLeftMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						// if right mouse button is released
						if (i == VK_RBUTTON)
						{
							// call event
							(*it)->onRightMouseUp(Point(current_mouse_pos.x, current_mouse_pos.y));
						}
						else
						{
							// call event
							(*it)->onKeyUp(i);
						}
						++it;
					}
				}

			}

		}
		// store current keys state to old keys state buffer
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

// add the subscriber to our inputSystem
void BNS_InputSystem::addListener(BNS_InputListener* listener)
{
	m_set_listeners.insert(listener);
}

// remove the subscriber to our inputSystem
void BNS_InputSystem::removeListener(BNS_InputListener* listener)
{
	m_set_listeners.erase(listener);
}

void BNS_InputSystem::setCursorPosition(const Point& pos)
{
	::SetCursorPos(pos.m_x, pos.m_y);
}

void BNS_InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

// return the reference of the singleton's instance
BNS_InputSystem* BNS_InputSystem::get()
{
	return m_system;
}

void BNS_InputSystem::create()
{
	if (BNS_InputSystem::m_system)
		throw std::exception("BNS_InputSystem already created");
	BNS_InputSystem::m_system = new BNS_InputSystem();
}

void BNS_InputSystem::release()
{
	if (!BNS_InputSystem::m_system)
		return;
	delete BNS_InputSystem::m_system;
}
