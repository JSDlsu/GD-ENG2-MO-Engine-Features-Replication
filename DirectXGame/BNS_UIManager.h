#pragma once
#include <vector>
#include <unordered_map>
#include "BNS_Window.h"
#include "BNS_AUIScreen.h"
#include "BNS_EnumHandler.h"
#include "BNS_Prerequisites.h"
#include "BNS_UI_Prerequisites.h"

class BNS_UICreation;
class BNS_MenuToolbar_UI;

class BNS_UIManager
{
public:
	typedef std::vector<AUIScreen_Ptr> uiScreenList;
	typedef std::unordered_map<BNS_UINames, AUIScreen_Ptr> uiScreenHashTable;

public:
	static BNS_UIManager* GetInstance();
	static void Initialize(BNS_AppWindow* appW, HWND hwnd, const RenderToTexturePtr render_tex[]);
	static void Release();
	static void HelpMarker(const char* desc);

	static BNS_UICreation* m_ui_creation;

	static float WINDOW_WIDTH;
	static float WINDOW_HEIGHT;
	static float SCENE_VIEW_WIDTH;
	static float SCENE_VIEW_HEIGHT;
	RenderToTexturePtr GetGameSceneView(int camID);
public:
	void DrawAllUIScreens();
	uiScreenHashTable GetUIHashTable();
private:
	uiScreenList GetUIList();
private:
	BNS_UIManager(BNS_AppWindow* appW, HWND hwnd, const RenderToTexturePtr render_tex[]);
	~BNS_UIManager();
	BNS_UIManager(BNS_UIManager const&) {};
	BNS_UIManager& operator=(BNS_UIManager const&) {};
	static BNS_UIManager* sharedInstance;
	
private:
	uiScreenList _uiScreenList;
	uiScreenHashTable uiTable;
	RenderToTexturePtr m_game_scene[4];
	BNS_AppWindow* m_app_window;
private:
	bool opt_fullscreen = true;
	bool opt_padding = true;
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	
private:
	friend class BNS_UICreation;
	friend class BNS_MenuToolbar_UI;
};


