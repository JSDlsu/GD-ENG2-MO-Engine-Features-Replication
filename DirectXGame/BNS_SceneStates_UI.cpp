#include "BNS_SceneStates_UI.h"
#include "BNS_Hierarchy_UI.h"
#include "BNS_UIManager.h"
#include "IMGUI/imgui_internal.h"
#include "BNS_ActionHistory.h"
#include "BNS_GameObjectManager.h"

BNS_SceneStates_UI::BNS_SceneStates_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
{
	
}

BNS_SceneStates_UI::~BNS_SceneStates_UI()
{
}

void BNS_SceneStates_UI::DrawUI()
{
	BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();

	std::string windowLabel = name + "##" + std::to_string(ID);
	if(ImGui::Begin(windowLabel.c_str()))
	{
		ImVec2 button_size = ImGui::CalcItemSize(ImVec2{ 150, 0 }, 0.0f, 0.0f);

		if (ImGui::Button("Undo")) {
			if (BNS_ActionHistory::GetInstance()->hasRemainingUndoActions()) {
				BNS_GameObjectManager::get()->applyEditorAction(BNS_ActionHistory::GetInstance()->undoAction());
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Redo")) {
			if (BNS_ActionHistory::GetInstance()->hasRemainingRedoActions()) {
				BNS_GameObjectManager::get()->applyEditorAction(BNS_ActionHistory::GetInstance()->redoAction());
			}
		}

		// obtain size of window
		ImVec2 avail = ImGui::GetWindowSize();

		// calculate centre of window for button. I recommend trying to figure out why this works!
		ImVec2 centre_position_for_button{
			// we have two buttons, so twice the size - and we need to account for the spacing in the middle
			(avail.x - button_size.x * 1 - ImGui::GetStyle().ItemSpacing.x) / 2,
			(avail.y - button_size.y) / 2
		};

		ImGui::SetCursorPos(centre_position_for_button);

		if (backend->getMode() == BNS_EngineBackend::EDITOR) {
			if (ImGui::Button("Play")) { BNS_EngineBackend::getInstance()->setMode(BNS_EngineBackend::PLAY); }
		}

		else if (backend->getMode() != BNS_EngineBackend::EDITOR) {
			if (ImGui::Button("Stop")) { BNS_EngineBackend::getInstance()->setMode(BNS_EngineBackend::EDITOR); }
		}

		ImGui::SameLine();

		if (backend->getMode() == BNS_EngineBackend::PLAY) {
			if (ImGui::Button("Pause")) { BNS_EngineBackend::getInstance()->setMode(BNS_EngineBackend::PAUSED); }
		}
		else if (backend->getMode() == BNS_EngineBackend::PAUSED) {
			if (ImGui::Button("Resume")) { BNS_EngineBackend::getInstance()->setMode(BNS_EngineBackend::PLAY); }
		}

		ImGui::SameLine();
		if (backend->getMode() == BNS_EngineBackend::PAUSED && ImGui::Button("Frame Step")) { BNS_EngineBackend::getInstance()->startFrameStep(); }
	}

	ImGui::End();
}