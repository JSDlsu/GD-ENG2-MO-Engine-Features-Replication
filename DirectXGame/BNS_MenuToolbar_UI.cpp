#include "BNS_MenuToolbar_UI.h"

#include "BNS_FileExplorer.h"
#include "BNS_PrimitiveCreation.h"
#include "BNS_Texture.h"
#include "BNS_UIManager.h"
#include "SceneWriter.h"
#include "SceneReader.h"

std::filesystem::path const BNS_MenuToolbar_UI::s_ScenePath = "Scene";

BNS_MenuToolbar_UI::BNS_MenuToolbar_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
{
	UM = BNS_UIManager::GetInstance();
	toShow = true;
}

BNS_MenuToolbar_UI::~BNS_MenuToolbar_UI()
{
}

void BNS_MenuToolbar_UI::DrawUI()
{
	if (ImGui::BeginMenuBar())
	{
		CreateTab_File();
		CreateTab_Edit();
		CreateTab_Assets();
		CreateTab_Gameobject();
		CreateTab_Components();
		CreateTab_Tools();
		CreateTab_Window();
		CreateTab_Help();
		ImGui::EndMenuBar();
	}
	
}

void BNS_MenuToolbar_UI::CreateTab_File()
{
	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("New Scene", NULL);
		if(ImGui::MenuItem("Open Scene", NULL))
		{
			SceneReader reader = SceneReader(s_ScenePath.string() + "/Test");
			reader.readFromFile();
		}
		if(ImGui::MenuItem("Save", NULL))
		{
			SceneWriter writer = SceneWriter(s_ScenePath.string() + "/Test");
			writer.writeToFile();
		};
		ImGui::MenuItem("Exit", NULL);
		ImGui::EndMenu();
	}
}

void BNS_MenuToolbar_UI::CreateTab_Edit()
{
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::MenuItem("Play", NULL);
		ImGui::MenuItem("Pause", NULL);
		//ImGui::MenuItem("Fullscreen", NULL, &UM->opt_fullscreen);
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
}

void BNS_MenuToolbar_UI::CreateTab_Assets()
{
	if (ImGui::BeginMenu("Assets"))
	{
		ImGui::MenuItem("Store", NULL);
		ImGui::EndMenu();
	}
}

void BNS_MenuToolbar_UI::CreateTab_Gameobject()
{
	if (ImGui::BeginMenu("GameObject"))
	{
		if (ImGui::MenuItem("Create Cube", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateCube();
		if (ImGui::MenuItem("Create Physics Cube", nullptr))
		{
			BNS_PrimitiveCreation::Instance()->CreateTexturedCube();
		}
		//BNS_PrimitiveCreation::Instance()->CreateTexturedCube();
		if (ImGui::MenuItem("Create Plane", nullptr))
			BNS_PrimitiveCreation::Instance()->CreatePlane();
		if (ImGui::MenuItem("Create Physics Plane", nullptr))
			BNS_PrimitiveCreation::Instance()->CreatePhysicsPlane();
		if (ImGui::MenuItem("Create Cylinder", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateCylinder();
		if (ImGui::MenuItem("Create Sphere", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateSphere();
		if (ImGui::MenuItem("Create Capsule", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateCapsule();
		if (ImGui::MenuItem("Create Teapot", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateTeapot();
		if (ImGui::MenuItem("Create Statue", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateStatue();
		if (ImGui::MenuItem("Create Bunny", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateBunny();
		if (ImGui::MenuItem("Create Armadillo", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateArmadillo();
		if (ImGui::MenuItem("Create Earth", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateEarth();
		if (ImGui::MenuItem("Create Scene", nullptr))
			BNS_PrimitiveCreation::Instance()->CreateScene();
		if (ImGui::MenuItem("Create 100 Physics Cubes", nullptr))
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					for (int k = 0; k < 4; k++)
					{
						std::cout << i << ", " << j << ", " << k << std::endl;
						BNS_PrimitiveCreation::Instance()->CreatePhysicsCube((float)i * 0.5, (float)j * 0.5 + 1.9f, (float)k * 0.5);
					}
				}
				
			}
		}
		ImGui::EndMenu();
	}
}

void BNS_MenuToolbar_UI::CreateTab_Components()
{
	if (ImGui::BeginMenu("Components"))
	{
		ImGui::MenuItem("Light", NULL);
		ImGui::EndMenu();
	}
}

void BNS_MenuToolbar_UI::CreateTab_Tools()
{
	if (ImGui::BeginMenu("Tools"))
	{
		ImGui::MenuItem("ProBuilder", NULL);
		ImGui::EndMenu();
	}
}

void BNS_MenuToolbar_UI::CreateTab_Window()
{
	if (ImGui::BeginMenu("Window"))
	{
		ImGui::MenuItem("Console", NULL, &UM->GetUIHashTable()[BNS_UINames::CONSOLE_SCREEN]->GetShow());
		ImGui::MenuItem("Profiler", NULL);
		ImGui::EndMenu();
	}
}

void BNS_MenuToolbar_UI::CreateTab_Help()
{
	static bool isAbout = false;
	if (ImGui::BeginMenu("Help"))
	{
		ImGui::MenuItem("About", NULL, &isAbout);
		ImGui::EndMenu();
	}
	if (isAbout)
	{
		//DRAW HERE
		ImGui::Begin("Credits");

		// assign the texture file to the BNS_Texture pointer by passing the its path in the file
		TexturePtr m_tex = BNS_FileExplorer::GetInstance()->GetImageHashTable()["dlsu_logo"];
		ImGui::Image((void*)m_tex.get()->GetShaderResourceView(), ImVec2(256, 256));

		ImGui::Text("About:");
		ImGui::Text("Scene Editor V.3.0");
		ImGui::Text("Developed By: Celestial, Emerson\nGaurana, Aldrey\nSantos, Joseph\nTallador, Eryn");
		ImGui::Text("SPECIAL THANKS");
		ImGui::Text("Sir Patrick");
		ImGui::Text("PardCode");
		ImGui::Text("ImGui: https://github.com/ocornut/imgui/tree/master");

		ImGui::End();
	}
}

