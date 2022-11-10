#include "BNS_FileExplorer.h"

#include "BNS_UICreation.h"
#include "BNS_UIManager.h"

BNS_FileExplorer* BNS_FileExplorer::sharedInstance = nullptr;

BNS_FileExplorer* BNS_FileExplorer::GetInstance()
{
	return sharedInstance;
}

void BNS_FileExplorer::Initialize()
{
	sharedInstance = new BNS_FileExplorer();
}

void BNS_FileExplorer::Release()
{
	delete sharedInstance;
}

void BNS_FileExplorer::InitializeFiles()
{
	imageTable["dlsu_logo"] =
		BNS_UIManager::m_ui_creation->CreateUI_Image(L"Assets\\Textures\\dlsu_logo.png");
	imageTable["file_icon"] =
		BNS_UIManager::m_ui_creation->CreateUI_Image(L"Assets\\Icons\\file_icon.png");
	imageTable["folder_icon"] =
		BNS_UIManager::m_ui_creation->CreateUI_Image(L"Assets\\Icons\\folder_icon.png");
}

BNS_FileExplorer::uiImageHashTable BNS_FileExplorer::GetImageHashTable()
{
	return imageTable;
}

BNS_FileExplorer::BNS_FileExplorer()
{
	InitializeFiles();
}

BNS_FileExplorer::~BNS_FileExplorer()
{
}
