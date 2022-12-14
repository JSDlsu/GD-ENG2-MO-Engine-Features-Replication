#define NOMINMAX
#include "BNS_Inspector_UI.h"
#include <limits>

#include "BNS_GameObjectManager.h"
#include "BNS_EngineTime.h"
#include "BNS_Hierarchy_UI.h"
#include "BNS_UIManager.h"
#include "BNS_ActionHistory.h"
#include "BNS_EngineBackend.h"

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

	if(BNS_EngineBackend::getInstance()->getMode() == BNS_EngineBackend::EDITOR)
	{
		BNS_AGameObject* selectedGO = dynamic_cast<BNS_Hierarchy_UI*>(
			BNS_UIManager::GetInstance()->GetUIHashTable()[BNS_UINames::HIERARCHY_SCREEN].get())->selectedGameObject;
		if (selectedGO == nullptr)
		{
			ImGui::End();
			return;
		}

		std::string nameString = "Selected Object Name: " + selectedGO->GetName();
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), nameString.c_str());
		ImGui::Text("\n");

		active = selectedGO->GetActive();
		if(ImGui::Checkbox("IsEnabled", &active))
		{
			selectedGO->SetActive(active);
		}
		

		bool show = selectedGO != nullptr;
		if (show && ImGui::CollapsingHeader("Transform"))
		{
			vec3 pos = { selectedGO->GetLocalPosition().m_x, selectedGO->GetLocalPosition().m_y, selectedGO->GetLocalPosition().m_z };
			vec3 scale = { selectedGO->GetLocalScale().m_x, selectedGO->GetLocalScale().m_y, selectedGO->GetLocalScale().m_z };
			vec3 rot = { selectedGO->GetLocalRotation().m_x, selectedGO->GetLocalRotation().m_y, selectedGO->GetLocalRotation().m_z };

			vec3 posCopy = { pos[0], pos[1], pos[2] };
			vec3 scaleCopy = { scale[0], scale[1], scale[2] };
			vec3 rotCopy = { rot[0], rot[1], rot[2] };

			//Position
			if (ImGui::DragFloat3("Position", pos, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max()))
			{
				if (ImGui::IsItemEdited())
					updateTransformDisplays(selectedGO, pos, scale, rot);
			}
			if (ImGui::IsItemDeactivatedAfterEdit())
			{

				BNS_ActionHistory::GetInstance()->recordAction(selectedGO->GetName());
			}
				

			//Rotate
			if (ImGui::DragFloat3("Rotation", rot, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max()))
			{
				if (ImGui::IsItemEdited())
					updateTransformDisplays(selectedGO, pos, scale, rot);
			}
			if (ImGui::IsItemDeactivatedAfterEdit())
				BNS_ActionHistory::GetInstance()->recordAction(selectedGO->GetName());

			//Scale
			if (ImGui::DragFloat3("Scale", scale, BNS_EngineTime::getDeltaTime(), (float)-std::numeric_limits<int>::max(), (float)std::numeric_limits<int>::max()))
			{
				if (ImGui::IsItemEdited())
					updateTransformDisplays(selectedGO, pos, scale, rot);
			}
			if (ImGui::IsItemDeactivatedAfterEdit())
				BNS_ActionHistory::GetInstance()->recordAction(selectedGO->GetName());

			/*
			//IMGUI SLIDER DEBUGGER
			ImGui::BulletText(
				"IsItemFocused() = %d\n"
				"IsItemHovered() = %d\n"
				"IsItemHovered(_AllowWhenBlockedByPopup) = %d\n"
				"IsItemHovered(_AllowWhenBlockedByActiveItem) = %d\n"
				"IsItemHovered(_AllowWhenOverlapped) = %d\n"
				"IsItemHovered(_AllowWhenDisabled) = %d\n"
				"IsItemHovered(_RectOnly) = %d\n"
				"IsItemActive() = %d\n"
				"IsItemEdited() = %d\n"
				"IsItemActivated() = %d\n"
				"IsItemDeactivated() = %d\n"
				"IsItemDeactivatedAfterEdit() = %d\n"
				"IsItemVisible() = %d\n"
				"IsItemClicked() = %d\n"
				"IsItemToggledOpen() = %d\n"
				"GetItemRectMin() = (%.1f, %.1f)\n"
				"GetItemRectMax() = (%.1f, %.1f)\n"
				"GetItemRectSize() = (%.1f, %.1f)",
				ImGui::IsItemFocused(),
				ImGui::IsItemHovered(),
				ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
				ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
				ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlapped),
				ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled),
				ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly),
				ImGui::IsItemActive(),
				ImGui::IsItemEdited(),
				ImGui::IsItemActivated(),
				ImGui::IsItemDeactivated(),
				ImGui::IsItemDeactivatedAfterEdit(),
				ImGui::IsItemVisible(),
				ImGui::IsItemClicked(),
				ImGui::IsItemToggledOpen(),
				ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y,
				ImGui::GetItemRectMax().x, ImGui::GetItemRectMax().y,
				ImGui::GetItemRectSize().x, ImGui::GetItemRectSize().y
			);
			*/

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
				static const char* items[] = { "Dynamic", "Kinematic" , "Static" };
				static int selectedItem = -1;

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


			if (ImGui::Button("Delete"))
			{
				BNS_GameObjectManager::get()->DeleteObject(selectedGO);
				selectedGO = nullptr;
				ImGui::End();
				return;
			}
				
		}
	}
	
	else
	{
		//ImGuiSlider
	}

	

	ImGui::End();
}

void BNS_Inspector_UI::updateTransformDisplays(BNS_AGameObject* gameObject, float pos[3], float scale[3], float rot[3])
{
		gameObject->SetPosition(pos[0], pos[1], pos[2]);
		gameObject->SetRotation(rot[0], rot[1], rot[2]);
		gameObject->SetScale(scale[0], scale[1], scale[2]);

		BNS_AComponent* physics_comp = gameObject->FindComponentOfType(ComponentType::Physics);
		if (physics_comp != nullptr)
		{
			BNS_PhysicsComponent* physicsComp = dynamic_cast<BNS_PhysicsComponent*>(physics_comp);
			BodyType bodyType = physicsComp->GetRigidBody()->getType();
			physicsComp->UpdateRigidBody();
			physicsComp->GetRigidBody()->setType(bodyType);
		}
}
