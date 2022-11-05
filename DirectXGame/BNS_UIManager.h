#pragma once
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "BNS_Window.h"
#include "BNS_AUIScreen.h"
#include "BNS_Credits_UI.h"
#include "BNS_EnumHandler.h"
#include "BNS_MenuToolbar_UI.h"


class BNS_UICreation;

class BNS_UIManager
{
public:
	typedef std::vector<AUIScreen_Ptr> uiScreenList;
	typedef std::unordered_map<BNS_UINames, AUIScreen_Ptr> uiScreenHashTable;

public:
	static BNS_UIManager* GetInstance();
	static void Initialize(HWND hwnd);
	static void Release();

	void DrawAllUIScreens();
	uiScreenList GetUIList();
	uiScreenHashTable GetUIHashTable();

	static const int WINDOW_WIDTH = 1366;
	static const int WINDOW_HEIGHT = 768;

private:
	BNS_UIManager(HWND hwnd);
	~BNS_UIManager();
	BNS_UIManager(BNS_UIManager const&) {};
	BNS_UIManager& operator=(BNS_UIManager const&) {};
	static BNS_UIManager* sharedInstance;

private:
	static BNS_UICreation* m_ui_creation;
	uiScreenList _uiScreenList;
	uiScreenHashTable uiTable;

private:
	friend class BNS_UICreation;
};


