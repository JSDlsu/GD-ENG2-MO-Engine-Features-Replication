#define NOMINMAX
#include "BNS_Inspector_UI.h"
#include <limits>

#include "BNS_GameObjectManager.h"
#include "BNS_AGameObject.h"
#include "BNS_EngineTime.h"
#include "BNS_Hierarchy_UI.h"
#include "BNS_UIManager.h"

BNS_Inspector_UI::BNS_Inspector_UI(std::string name) : BNS_AUIScreen(name)
{
}

BNS_Inspector_UI::~BNS_Inspector_UI()
{
}

typedef float vec3[3];
void BNS_Inspector_UI::DrawUI()
{
	//DRAW HERE
	ImGui::Begin("Inspector");
	AGameObjectPtr selectedGO = dynamic_cast<BNS_Hierarchy_UI*>(
		BNS_UIManager::GetInstance()->GetUIHashTable()[BNS_UINames::HIERARCHY_SCREEN].get())->selectedGameObject;
	bool show = selectedGO != nullptr;
	if ( show && ImGui::CollapsingHeader("Transform"))
	{
		vec3 pos = { selectedGO.get()->GetLocalPosition().m_x, selectedGO.get()->GetLocalPosition().m_y, selectedGO.get()->GetLocalPosition().m_z };
		vec3 scale = { selectedGO.get()->GetLocalScale().m_x, selectedGO.get()->GetLocalScale().m_y, selectedGO.get()->GetLocalScale().m_z };
		vec3 rot = { selectedGO.get()->GetLocalRotation().m_x, selectedGO.get()->GetLocalRotation().m_y, selectedGO.get()->GetLocalRotation().m_z };

		ImGui::DragFloat3("Position", pos, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Rotation", rot, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Scale", scale, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());

		selectedGO.get()->SetPosition(pos[0], pos[1], pos[2]);
		selectedGO.get()->SetRotation(rot[0], rot[1], rot[2]);
		selectedGO.get()->SetScale(scale[0], scale[1], scale[2]);
	}


	ImGui::End();
}
