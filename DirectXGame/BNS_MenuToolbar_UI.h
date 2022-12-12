#pragma once
#include "BNS_AUIScreen.h"
#include "BNS_CameraHandler.h"
#include "BNS_Camera.h"
#include <filesystem>

class BNS_MenuToolbar_UI : public BNS_AUIScreen
{
public:
	BNS_MenuToolbar_UI(std::string name, int ID);
	~BNS_MenuToolbar_UI();
	void DrawUI() override;
private:
	BNS_UIManager* UM = nullptr;
private:
	void CreateTab_File();
	void CreateTab_Edit();
	void CreateTab_Assets();
	void CreateTab_Gameobject();
	void CreateTab_Components();
	void CreateTab_Tools();
	void CreateTab_Window();
	void CreateTab_Help();
public:
	static const std::filesystem::path s_ScenePath;
};

