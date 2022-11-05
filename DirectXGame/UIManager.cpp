#include "UIManager.h"
#include "BNS_GraphicsEngine.h"
#include "UICreation.h"

UIManager* UIManager::sharedInstance = nullptr;
UICreation* UIManager::m_ui_creation = nullptr;

UIManager* UIManager::GetInstance()
{
	return sharedInstance;
}

void UIManager::Initialize(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);

	// initialize the UI screens
	m_ui_creation->CreateCreditsUI();
	m_ui_creation->CreateMenuToolbarUI();
}

void UIManager::Release()
{
	delete sharedInstance;
}

void UIManager::DrawAllUIScreens()
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

UIManager::uiScreenList UIManager::GetUIList()
{
	return _uiScreenList;
}

UIManager::uiScreenHashTable UIManager::GetUIHashTable()
{
	return uiTable;
}

UIManager::UIManager(HWND hwnd)
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
		// instantiate our RenderSystem
		m_ui_creation = new UICreation();
	}
	catch (...)
	{
		throw std::exception("UICreation not created successfully");
	}
}

UIManager::~UIManager()
{
}


