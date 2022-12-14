#include "BNS_ViewMode_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"

BNS_ViewMode_UI::BNS_ViewMode_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
{
}

BNS_ViewMode_UI::~BNS_ViewMode_UI()
{
}

void BNS_ViewMode_UI::DrawUI()
{
	static const char* items[] = { "Perspective", "Orthographic" };
	static int selectedItem = 0;

	//DRAW HERE
	ImGui::Begin("View Mode");
	ImGui::Combo("Camera", &selectedItem, items, IM_ARRAYSIZE(items));
	//std::cout << "selected:" << selectedItem << std::endl;
	if (selectedItem == 0)
	{
		dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->SetPerspectiveMode(true);
		ImGui::SliderFloat("FOV", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().fovInDegrees,
			1, 179, "%.2f");
		ImGui::SliderFloat("AspectRatio", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().aspectRatio,
			0.8f, 2.44f, "%.2f");
		ImGui::SliderFloat("NearPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().nearPlane,
			0.01f, dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().farPlane - 0.01f, "%.2f");
		ImGui::SliderFloat("FarPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().farPlane,
			0.02f, 1000.0f, "%.2f");
	}
	else
	{
		dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->SetPerspectiveMode(false);
		ImGui::SliderFloat("FOV", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().fovInDegrees,
			1, 179, "%.2f");
		ImGui::SliderFloat("AspectRatio", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().aspectRatio,
			0.8f, 2.44f, "%.2f");
		ImGui::SliderFloat("NearPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().nearPlane,
			0.01f, dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().farPlane - 0.01f, "%.2f");
		ImGui::SliderFloat("FarPlane", &dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().farPlane,
			0.02f, 1000.0f, "%.2f");
	}
	//std::cout << "Value: " << f4 << std::endl;

	dynamic_cast<BNS_Camera*>(BNS_CameraHandler::GetInstance()->GetSceneCamera())->GetCamProperties().aspectRatio =
		BNS_UIManager::SCENE_VIEW_WIDTH / BNS_UIManager::SCENE_VIEW_HEIGHT;

	ImGui::End();
}
