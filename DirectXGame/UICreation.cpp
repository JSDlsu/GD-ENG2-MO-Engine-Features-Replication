#include "UICreation.h"
#include "Credits_UI.h"
#include "UIManager.h"

UICreation::UICreation()
{
}

UICreation::~UICreation()
{
}

void UICreation::CreateCreditsUI()
{
	Credits_UI* screen = new Credits_UI("creditsUI");
	AUIScreen_Ptr ptr_screen(screen);
	UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);
	UIManager::GetInstance()->uiTable[UINames::CREDITS_SCREEN] = ptr_screen;
	
}

void UICreation::CreateMenuToolbarUI()
{
	MenuToolbar_UI* screen = new MenuToolbar_UI("menuToolbar");
	AUIScreen_Ptr ptr_screen(screen);
	UIManager::GetInstance()->uiTable[UINames::MENU_SCREEN] = ptr_screen;
	UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);

}
