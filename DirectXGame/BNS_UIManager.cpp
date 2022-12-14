#include "BNS_UIManager.h"

#include "BNS_AppWindow.h"
#include "BNS_CameraHandler.h"
#include "BNS_FileExplorer.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_RenderToTexture.h"
#include "BNS_UICreation.h"

BNS_UIManager* BNS_UIManager::sharedInstance = nullptr;
BNS_UICreation* BNS_UIManager::m_ui_creation = nullptr;

float BNS_UIManager::WINDOW_WIDTH = 1920;
float BNS_UIManager::WINDOW_HEIGHT = 1080;
float BNS_UIManager::SCENE_VIEW_WIDTH = 400.0f;
float BNS_UIManager::SCENE_VIEW_HEIGHT = 400.0f;
	
BNS_UIManager* BNS_UIManager::GetInstance()
{
	return sharedInstance;
}

void BNS_UIManager::Initialize(BNS_AppWindow* appW, HWND hwnd, const RenderToTexturePtr render_tex[])
{
	sharedInstance = new BNS_UIManager(appW, hwnd, render_tex);
	// initialize file explorer
	BNS_FileExplorer::Initialize();

	// initialize the UI screens
	m_ui_creation->CreateMenuToolbarUI();
	m_ui_creation->CreateHierarchyUI();

	m_ui_creation->CreateSceneViewUI();
	m_ui_creation->CreateSceneViewUI();
	m_ui_creation->CreateSceneViewUI();
	m_ui_creation->CreateSceneViewUI();
	m_ui_creation->CreateViewModeUI();

	m_ui_creation->CreateContentBrowserUI();
	m_ui_creation->CreateConsoleUI();
	m_ui_creation->CreateInspectorUI();
	m_ui_creation->CreateSceneStatesUI();
	//m_ui_creation->CreateInspectorUI();
}


void BNS_UIManager::Release()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	// release file explorer
	BNS_FileExplorer::Release();
	delete sharedInstance;
}

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
void BNS_UIManager::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

RenderToTexturePtr BNS_UIManager::GetGameSceneView(int camID)
{
	return m_game_scene[camID];
}

void BNS_UIManager::DrawAllUIScreens()
{
	//START IMGUI FRAME
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;
	
	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	// NOTE: Screens should be within the dockspace for them to be dockable
	// Start DockSpace
	ImGui::Begin("DockSpace Demo", nullptr, window_flags);
	if (!opt_padding)
		ImGui::PopStyleVar();
	if (opt_fullscreen)
		ImGui::PopStyleVar(2);
	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	// Call each UIScreen members in the list
	uiScreenList::iterator i;
	for (i = _uiScreenList.begin(); i != _uiScreenList.end(); ++i)
	{
		// screens to show should be within the dockspace code
		if ((*i)->toShow)
		{
			(*i)->DrawUI();
		}
	}
	// End DockSpace
	ImGui::End();
	RECT size_screen = m_app_window->getSizeScreen();
	WINDOW_WIDTH = size_screen.right;
	WINDOW_HEIGHT = size_screen.bottom;
	io.DisplaySize = ImVec2(size_screen.right, size_screen.bottom);
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// Update and Render additional Platform Windows
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

BNS_UIManager::uiScreenList BNS_UIManager::GetUIList()
{
	return _uiScreenList;
}

BNS_UIManager::uiScreenHashTable BNS_UIManager::GetUIHashTable()
{
	return uiTable;
}

BNS_UIManager::BNS_UIManager(BNS_AppWindow* appW, HWND hwnd, const RenderToTexturePtr render_tex[])
{
	// assign app window reference
	m_app_window = appW;
	// assign game scene render reference
	m_game_scene[0] = render_tex[0];
	m_game_scene[1] = render_tex[1];
	m_game_scene[2] = render_tex[2];
	m_game_scene[3] = render_tex[3];

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// Change font setting
	float fontSize = 18.0f;
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans-Bold.ttf", fontSize);
	io.FontDefault = io.Fonts->AddFontFromFileTTF("Assets/Fonts/OpenSans-Regular.ttf", fontSize);

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(BNS_GraphicsEngine::get()->getRenderSystem()->GetDevice(), 
		BNS_GraphicsEngine::get()->getRenderSystem()->GetDeviceContext());

	try
	{
		// instantiate our BNS_RenderSystem
		m_ui_creation = new BNS_UICreation();
	}
	catch (...)
	{
		throw std::exception("BNS_UICreation not created successfully");
	}
}

BNS_UIManager::~BNS_UIManager()
{
}


