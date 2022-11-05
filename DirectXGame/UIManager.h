#pragma once
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Window.h"
#include "AUIScreen.h"
#include "Credits_UI.h"
#include "BNS_EnumHandler.h"
#include "MenuToolbar_UI.h"


class UICreation;

class UIManager
{
public:
	typedef std::vector<AUIScreen_Ptr> uiScreenList;
	typedef std::unordered_map<BNS_UINames, AUIScreen_Ptr> uiScreenHashTable;

public:
	static UIManager* GetInstance();
	static void Initialize(HWND hwnd);
	static void Release();

	void DrawAllUIScreens();
	uiScreenList GetUIList();
	uiScreenHashTable GetUIHashTable();

	static const int WINDOW_WIDTH = 1366;
	static const int WINDOW_HEIGHT = 768;

private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

private:
	static UICreation* m_ui_creation;
	uiScreenList _uiScreenList;
	uiScreenHashTable uiTable;

private:
	friend class UICreation;
};


