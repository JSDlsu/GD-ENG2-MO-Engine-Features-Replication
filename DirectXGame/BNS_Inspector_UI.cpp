#define NOMINMAX
#include "BNS_Inspector_UI.h"
#include <limits>

#include "BNS_GameObjectManager.h"
#include "BNS_AGameObject.h"
#include "BNS_EngineTime.h"
#include "BNS_Hierarchy_UI.h"
#include "BNS_UIManager.h"

BNS_Inspector_UI::BNS_Inspector_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
{

}

BNS_Inspector_UI::~BNS_Inspector_UI()
{
}

typedef float vec3[3];
void BNS_Inspector_UI::DrawUI()
{
	//DRAW HERE
	std::string windowLabel = name + "##" + std::to_string(ID);
	ImGui::Begin(windowLabel.c_str());
	BNS_AGameObject* selectedGO = dynamic_cast<BNS_Hierarchy_UI*>(
		BNS_UIManager::GetInstance()->GetUIHashTable()[BNS_UINames::HIERARCHY_SCREEN].get())->selectedGameObject;
	if (selectedGO == nullptr)
	{
		ImGui::End();
		return;
	}
	bool show = selectedGO != nullptr;
	if ( show && ImGui::CollapsingHeader("Transform"))
	{
		vec3 pos = { selectedGO->GetLocalPosition().m_x, selectedGO->GetLocalPosition().m_y, selectedGO->GetLocalPosition().m_z };
		vec3 scale = { selectedGO->GetLocalScale().m_x, selectedGO->GetLocalScale().m_y, selectedGO->GetLocalScale().m_z };
		vec3 rot = { selectedGO->GetLocalRotation().m_x, selectedGO->GetLocalRotation().m_y, selectedGO->GetLocalRotation().m_z };

		ImGui::DragFloat3("Position", pos, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Rotation", rot, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());
		ImGui::DragFloat3("Scale", scale, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max());

		selectedGO->SetPosition(pos[0], pos[1], pos[2]);
		selectedGO->SetRotation(rot[0], rot[1], rot[2]);
		selectedGO->SetScale(scale[0], scale[1], scale[2]);
	}
	if (selectedGO != nullptr)
	{
		// use to access physics component
		BNS_AComponent* physics_comp = selectedGO->FindComponentOfType(ComponentType::Physics);
		if (physics_comp != nullptr)
		{
			ImGui::Separator();
			BNS_PhysicsComponent* physicsComp = dynamic_cast<BNS_PhysicsComponent*>(physics_comp);

			
			//ImGui::Text("Body Type");
			static const char* items[] = { "Dynamic", "Kinematic" , "Static"};
			static int selectedItem;

			if (physicsComp->GetRigidBody()->getType() == BodyType::DYNAMIC)
				selectedItem = 0;
			else if (physicsComp->GetRigidBody()->getType() == BodyType::KINEMATIC)
				selectedItem = 1;
			else if (physicsComp->GetRigidBody()->getType() == BodyType::STATIC)
				selectedItem = 2;

			ImGui::Combo("Body Type", &selectedItem, items, IM_ARRAYSIZE(items));
			if (selectedItem == 0)
			{
				physicsComp->GetRigidBody()->setType(BodyType::DYNAMIC);
			}
			else if (selectedItem == 1)
			{
				physicsComp->GetRigidBody()->setType(BodyType::KINEMATIC);
			}
			else if (selectedItem == 2)
			{
				physicsComp->GetRigidBody()->setType(BodyType::STATIC);
			}
		}
	}
	


	ImGui::End();
}
