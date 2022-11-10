#pragma once
#include <vector>
#include <unordered_map>
#include "BNS_Window.h"
#include "BNS_AUIScreen.h"
#include "BNS_EnumHandler.h"
#include "BNS_Prerequisites.h"


class BNS_UICreation;
class BNS_MenuToolbar_UI;

class BNS_UIManager
{
public:
	typedef std::vector<AUIScreen_Ptr> uiScreenList;
	typedef std::unordered_map<BNS_UINames, AUIScreen_Ptr> uiScreenHashTable;

public:
	static BNS_UIManager* GetInstance();
	static void Initialize(HWND hwnd, const RenderToTexturePtr& render_tex);
	static void Release();
	static void HelpMarker(const char* desc);

	static BNS_UICreation* m_ui_creation;

	static const int WINDOW_WIDTH = 1920;
	static const int WINDOW_HEIGHT = 1080;
	RenderToTexturePtr GetGameSceneView();
public:
	void DrawAllUIScreens();
	uiScreenHashTable GetUIHashTable();
private:
	uiScreenList GetUIList();
private:
	BNS_UIManager(HWND hwnd, const RenderToTexturePtr& render_tex);
	~BNS_UIManager();
	BNS_UIManager(BNS_UIManager const&) {};
	BNS_UIManager& operator=(BNS_UIManager const&) {};
	static BNS_UIManager* sharedInstance;
	
    // Our state
    bool show_demo_window = true;
private:
	uiScreenList _uiScreenList;
	uiScreenHashTable uiTable;
	RenderToTexturePtr m_game_scene;
private:
	bool opt_fullscreen = true;
	bool opt_padding = true;
	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	
private:
	friend class BNS_UICreation;
	friend class BNS_MenuToolbar_UI;
};


