#include "BNS_UICreation.h"
#include "BNS_Credits_UI.h"
#include "BNS_UIManager.h"

BNS_UICreation::BNS_UICreation()
{
}

BNS_UICreation::~BNS_UICreation()
{
}

void BNS_UICreation::CreateCreditsUI()
{
	BNS_Credits_UI* screen = new BNS_Credits_UI("creditsUI");
	AUIScreen_Ptr ptr_screen(screen);
	BNS_UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);
	BNS_UIManager::GetInstance()->uiTable[BNS_UINames::CREDITS_SCREEN] = ptr_screen;
	
}

void BNS_UICreation::CreateMenuToolbarUI()
{
	BNS_MenuToolbar_UI* screen = new BNS_MenuToolbar_UI("menuToolbar");
	AUIScreen_Ptr ptr_screen(screen);
	BNS_UIManager::GetInstance()->uiTable[BNS_UINames::MENU_SCREEN] = ptr_screen;
	BNS_UIManager::GetInstance()->_uiScreenList.push_back(ptr_screen);

}
