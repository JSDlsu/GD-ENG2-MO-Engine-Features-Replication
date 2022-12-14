#include "BNS_SceneView_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_RenderToTexture.h"
#include "BNS_UIManager.h"

BNS_SceneView_UI::BNS_SceneView_UI(std::string name, int ID, int cameraID) : BNS_AUIScreen(name, ID)
{
	this->cameraID = cameraID;
}

BNS_SceneView_UI::~BNS_SceneView_UI()
{
}

void BNS_SceneView_UI::DrawUI()
{

	std::string windowLabel = name + "##" + std::to_string(ID);
	ImGui::Begin(windowLabel.c_str());
	ImVec2 game_scene_size = ImGui::GetWindowSize();
	// updates the scene view width and height 
	BNS_UIManager::SCENE_VIEW_WIDTH = game_scene_size.x;
	BNS_UIManager::SCENE_VIEW_HEIGHT = game_scene_size.y;
	ImGui::Image(BNS_UIManager::GetInstance()->GetGameSceneView(cameraID).get()->GetShaderResourceView(),
		game_scene_size); // render texture 
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow))
	{
		BNS_CameraHandler::GetInstance()->currentCamIndex = cameraID;
		std::cout << "Current Camera ID: " << BNS_CameraHandler::GetInstance()->currentCamIndex << "\n";
	}
	ImGui::End();

}
