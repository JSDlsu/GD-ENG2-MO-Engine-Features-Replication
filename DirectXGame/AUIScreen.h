#pragma once

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include <string>
#include <iostream>
#include "UI_Prerequisites.h"
#include "EnumHandler.h"

class AUIScreen
{
protected:
	AUIScreen(std::string name);
	~AUIScreen();

	std::string GetName();

public:
	virtual void DrawUI() = 0;

public:
	bool toShow = true;

protected:
	std::string name;

protected:
	friend class UIManager;
};

