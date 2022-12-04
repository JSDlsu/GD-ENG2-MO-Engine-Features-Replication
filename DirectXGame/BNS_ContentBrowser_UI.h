#pragma once
#include <filesystem>
#include "BNS_AUIScreen.h"

class BNS_ContentBrowser_UI : public BNS_AUIScreen
{
public:
	BNS_ContentBrowser_UI(std::string name, int ID);
	~BNS_ContentBrowser_UI();
	void DrawUI() override;
private:
	static const std::filesystem::path s_AssetPath;
	std::filesystem::path m_CurrentDirectory;
};

