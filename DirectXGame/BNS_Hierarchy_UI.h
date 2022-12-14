#pragma once
#include <vector>

#include "BNS_AUIScreen.h"
#include "BNS_Prerequisites.h"

class BNS_AGameObject;
class BNS_Inspector_UI;

class BNS_Hierarchy_UI : public BNS_AUIScreen
{
public:
	BNS_Hierarchy_UI(std::string name, int ID);
	~BNS_Hierarchy_UI();
	void DrawUI() override;
public:
	BNS_AGameObject* GetSelectedGO();
private:
	BNS_AGameObject* selectedGameObject = nullptr;
	void OpenChildList(std::vector<BNS_AGameObject*> objects);
private:
	friend class BNS_Inspector_UI;
};

