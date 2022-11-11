#include "BNS_MenuToolbar_UI.h"

#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_UIManager.h"
#include "IMGUI/imgui_internal.h"
#include "BNS_StructHandler.h"

BNS_MenuToolbar_UI::BNS_MenuToolbar_UI(std::string name) : BNS_AUIScreen(name)
{
	toShow = true;
}

BNS_MenuToolbar_UI::~BNS_MenuToolbar_UI()
{
}

void BNS_MenuToolbar_UI::DrawUI()
{
	BNS_UIManager* UM =  BNS_UIManager::GetInstance();
	if (ImGui::BeginMenuBar())
	{
		
		// About GameEngine
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Credits", NULL, &UM->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			ImGui::MenuItem("Fullscreen", NULL, &UM->opt_fullscreen);
			ImGui::MenuItem("Padding", NULL, &UM->opt_padding);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoSplit", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (UM->dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (UM->dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, UM->opt_fullscreen)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Assets"))
		{
			ImGui::MenuItem("Credits", NULL, &UM->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameObject"))
		{

			ImGui::MenuItem("PRIMITIVES", NULL, &UM->GetUIHashTable()[BNS_UINames::GAMEOBJECT_SCREEN]->toShow);
			ImGui::MenuItem("CUBE", NULL, &UM->GetUIHashTable()[BNS_UINames::GAMEOBJECT_SCREEN]->toShow);
			ImGui::MenuItem("PLANE", NULL, &UM->GetUIHashTable()[BNS_UINames::GAMEOBJECT_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Components"))
		{
			ImGui::MenuItem("Credits", NULL, &UM->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::MenuItem("Credits", NULL, &UM->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			ImGui::MenuItem("CONSOLE", NULL, &UM->GetUIHashTable()[BNS_UINames::CONSOLE_SCREEN]->toShow);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Credits", NULL, &UM->GetUIHashTable()[BNS_UINames::CREDITS_SCREEN]->toShow);
			ImGui::EndMenu();
			
		}

		// WindowOptions
		/*if (ImGui::BeginMenu("Options"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, &UM->opt_fullscreen);
			ImGui::MenuItem("Padding", NULL, &UM->opt_padding);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoSplit", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (UM->dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (UM->dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (UM->dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, UM->opt_fullscreen)) { UM->dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();
			ImGui::EndMenu();
		}*/

	
		
		

		ImGui::EndMenuBar();
	}

	static const char* items[] = { "Perspective", "Orthographic" };
	static int selectedItem = 0;





	
	//DRAW HERE
	ImGui::Begin("View Mode");
		ImGui::Combo("Camera", &selectedItem, items, IM_ARRAYSIZE(items));
		//std::cout << "selected:" << selectedItem << std::endl;
		if( selectedItem == 0)
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


	
		ImGui::End();
	
	

	
	
}
