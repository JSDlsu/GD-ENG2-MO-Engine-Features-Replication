#include "BNS_SceneView_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_RenderToTexture.h"
#include "BNS_UIManager.h"

BNS_SceneView_UI::BNS_SceneView_UI(std::string name) : BNS_AUIScreen(name)
{
}

BNS_SceneView_UI::~BNS_SceneView_UI()
{
}

void BNS_SceneView_UI::DrawUI()
{
	ImGui::Begin("GameScene");
	ImVec2 game_scene_size = ImGui::GetWindowSize();
	// updates the scene view width and height 
	BNS_UIManager::SCENE_VIEW_WIDTH = game_scene_size.x;
	BNS_UIManager::SCENE_VIEW_HEIGHT = game_scene_size.y;
	ImGui::Image(BNS_UIManager::GetInstance()->GetGameSceneView().get()->GetShaderResourceView(),
		game_scene_size); // render texture 
	ImGui::End();


	static const char* items[] = { "Perspective", "Orthographic" };
	static int selectedItem = 0;

	//DRAW HERE
	ImGui::Begin("View Mode");
	ImGui::Combo("Camera", &selectedItem, items, IM_ARRAYSIZE(items));
	//std::cout << "selected:" << selectedItem << std::endl;
	if (selectedItem == 0)
	{
		dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->SetPerspectiveMode(true);
		ImGui::SliderFloat("FOV", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().fovInDegrees,
			1, 179, "%.2f");
		ImGui::SliderFloat("AspectRatio", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().aspectRatio,
			0.8f, 2.44f, "%.2f");
		ImGui::SliderFloat("NearPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().nearPlane,
			0.01f, dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().farPlane - 0.01f, "%.2f");
		ImGui::SliderFloat("FarPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().farPlane,
			0.02f, 1000.0f, "%.2f");
	}
	else
	{
		dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->SetPerspectiveMode(false);
		ImGui::SliderFloat("FOV", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().fovInDegrees,
			1, 179, "%.2f");
		ImGui::SliderFloat("AspectRatio", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().aspectRatio,
			0.8f, 2.44f, "%.2f");
		ImGui::SliderFloat("NearPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().nearPlane,
			0.01f, dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().farPlane - 0.01f, "%.2f");
		ImGui::SliderFloat("FarPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().farPlane,
			0.02f, 1000.0f, "%.2f");
	}
	//std::cout << "Value: " << f4 << std::endl;

	if (ImGui::Button("Fix AspectRatio"))
	{
		dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera().get())->GetCamProperties().aspectRatio =
			BNS_UIManager::SCENE_VIEW_WIDTH / BNS_UIManager::SCENE_VIEW_HEIGHT;
	}

	ImGui::End();
}
