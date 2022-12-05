#pragma once

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include <string>
#include <iostream>
#include "BNS_UI_Prerequisites.h"

class BNS_AUIScreen
{
public:
	virtual void DrawUI() = 0;
public:
	bool& GetShow();
public:
	BNS_AUIScreen(std::string name, int ID);
	~BNS_AUIScreen();
	std::string GetName();
	int GetID();
protected:
	std::string name;
	int ID;
	bool toShow = true;
protected:
	friend class BNS_UIManager;
};

