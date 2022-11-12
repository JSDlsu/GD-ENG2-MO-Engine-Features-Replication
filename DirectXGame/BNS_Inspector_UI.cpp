#define NOMINMAX
#include "BNS_Inspector_UI.h"
#include <limits>

#include "BNS_GameObjectManager.h"
#include "BNS_AGameObject.h"
#include "BNS_UIManager.h"

BNS_Inspector_UI::BNS_Inspector_UI(std::string name) : BNS_AUIScreen(name)
{
}

BNS_Inspector_UI::~BNS_Inspector_UI()
{
}

void BNS_Inspector_UI::DrawUI()
{
	//DRAW HERE
	ImGui::Begin("Inspector");
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::DragFloat3("Position", positionTest, 0.5f, (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Rotation", rotationTest, 0.5f, (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Scale", scaleTest, 0.1f, (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
	}


	ImGui::End();
}
