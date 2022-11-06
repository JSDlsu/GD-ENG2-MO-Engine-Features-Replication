#include "BNS_UIManager.h"

#include "BNS_FileExplorer.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_UICreation.h"

BNS_UIManager* BNS_UIManager::sharedInstance = nullptr;
BNS_UICreation* BNS_UIManager::m_ui_creation = nullptr;

BNS_UIManager* BNS_UIManager::GetInstance()
{
	return sharedInstance;
}

void BNS_UIManager::Initialize(HWND hwnd)
{
	sharedInstance = new BNS_UIManager(hwnd);
	// initialize file explorer
	BNS_FileExplorer::Initialize();

	// initialize the UI screens
	m_ui_creation->CreateCreditsUI();
	m_ui_creation->CreateMenuToolbarUI();
}

void BNS_UIManager::Release()
{
	// release file explorer
	BNS_FileExplorer::Release();
	delete sharedInstance;
}

void BNS_UIManager::DrawAllUIScreens()
{
	//START IMGUI FRAME
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Call each UIScreen members in the list
	uiScreenList::iterator i;
	for (i = _uiScreenList.begin(); i != _uiScreenList.end(); ++i)
	{
		if ((*i)->toShow)
		{
			(*i)->DrawUI();
		}
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

BNS_UIManager::uiScreenList BNS_UIManager::GetUIList()
{
	return _uiScreenList;
}

BNS_UIManager::uiScreenHashTable BNS_UIManager::GetUIHashTable()
{
	return uiTable;
}

BNS_UIManager::BNS_UIManager(HWND hwnd)
{
	// Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(BNS_GraphicsEngine::get()->getRenderSystem()->GetDevice(), BNS_GraphicsEngine::get()->getRenderSystem()->GetDeviceContext());
	ImGui::StyleColorsDark();

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


