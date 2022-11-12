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
protected:
	BNS_AUIScreen(std::string name);
	~BNS_AUIScreen();
	std::string GetName();
protected:
	std::string name;
	bool toShow = true;
protected:
	friend class BNS_UIManager;
};

