#pragma once

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include <string>
#include <iostream>
#include "BNS_UI_Prerequisites.h"
#include "BNS_EnumHandler.h"

class BNS_AUIScreen
{
protected:
	BNS_AUIScreen(std::string name);
	~BNS_AUIScreen();

	std::string GetName();

public:
	virtual void DrawUI() = 0;

public:
	bool toShow = true;

protected:
	std::string name;

protected:
	friend class BNS_UIManager;
};

