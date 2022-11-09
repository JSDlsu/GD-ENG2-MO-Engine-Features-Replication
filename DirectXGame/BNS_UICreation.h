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
	void CreateCreditsUI();
	void CreateMenuToolbarUI();
	void CreateHierarchyUI();
	void CreateSceneViewUI();
};

