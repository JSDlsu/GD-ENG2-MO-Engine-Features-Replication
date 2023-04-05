#pragma once
#include "BNS_Prerequisites.h"
#include "BNS_UI_Prerequisites.h"

struct ImVec2;

class BNS_UICreation
{
public:
	BNS_UICreation();
	~BNS_UICreation();
public:
	TexturePtr CreateUI_Image(const wchar_t* tex_path);
	void CreateMenuToolbarUI();
	void CreateHierarchyUI();
	void CreateSceneViewUI();
	void CreateContentBrowserUI();
	void CreateConsoleUI();
	void CreateInspectorUI();
	void CreateSceneStatesUI();
	void CreateViewModeUI();
	void CreateMultipleSceneUI();

private:
	int currentID = 0;
};

