#include "BNS_UICreation.h"

#include "BNS_ContentBrowser_UI.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_Hierarchy_UI.h"
#include "BNS_MenuToolbar_UI.h"
#include "BNS_SceneView_UI.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"
#include  "BNS_Console_UI.h"

BNS_UICreation::BNS_UICreation()
{
}

BNS_UICreation::~BNS_UICreation()
{
}

TexturePtr BNS_UICreation::CreateUI_Image(const wchar_t* tex_path)
{
	// assign the texture file to the BNS_Texture pointer by passing the its path in the file
	TexturePtr m_tex = BNS_GraphicsEngine::get()->getTextureManager()->createTextureFromFile(tex_path);

	return m_tex;
}

void BNS_UICreation::CreateMenuToolbarUI()
{
	BNS_MenuToolbar_UI* screen = new BNS_MenuToolbar_UI("menuToolbar");
	AUIScreen_Ptr ptr_screen(screen);
	BNS_UIManager::GetInstance()->uiTable[BNS_UINames::MENU_SCREEN] = ptr_screen;
	BNS_UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);

}

void BNS_UICreation::CreateHierarchyUI()
{
	BNS_Hierarchy_UI* screen = new BNS_Hierarchy_UI("hierarchyUI");
	AUIScreen_Ptr ptr_screen(screen);
	BNS_UIManager::GetInstance()->uiTable[BNS_UINames::HIERARCHY_SCREEN] = ptr_screen;
	BNS_UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);

}

void BNS_UICreation::CreateSceneViewUI()
{
	BNS_SceneView_UI* screen = new BNS_SceneView_UI("sceneViewUI");
	AUIScreen_Ptr ptr_screen(screen);
	BNS_UIManager::GetInstance()->uiTable[BNS_UINames::SCENEVIEW_SCREEN] = ptr_screen;
	BNS_UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);

}

void BNS_UICreation::CreateContentBrowserUI()
{
	BNS_ContentBrowser_UI* screen = new BNS_ContentBrowser_UI("contentBrowserUI");
	AUIScreen_Ptr ptr_screen(screen);
	BNS_UIManager::GetInstance()->uiTable[BNS_UINames::CONTENT_BROWSER_SCREEN] = ptr_screen;
	BNS_UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);

}

void BNS_UICreation::CreateConsoleUI()
{
	BNS_Console_UI* screen = new BNS_Console_UI("GameObjectUI");
	AUIScreen_Ptr ptr_screen(screen);
	BNS_UIManager::GetInstance()->uiTable[BNS_UINames::CONSOLE_SCREEN] = ptr_screen;
	BNS_UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);

}