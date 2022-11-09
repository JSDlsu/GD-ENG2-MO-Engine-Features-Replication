#include "BNS_SceneView_UI.h"

#include "BNS_RenderToTexture.h"
#include "BNS_UIManager.h"

BNS_SceneView_UI::BNS_SceneView_UI(std::string name) : BNS_AUIScreen(name)
{
}

void BNS_SceneView_UI::DrawUI()
{
	ImGui::Begin("GameScene");
	ImVec2 game_scene_size = ImGui::GetWindowSize();
	ImGui::Image(BNS_UIManager::GetInstance()->GetGameSceneView().get()->GetShaderResourceView(),
		game_scene_size); // render texture 
	ImGui::End();
}
