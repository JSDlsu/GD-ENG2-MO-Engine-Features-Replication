#include "BNS_MultipleScene_UI.h"
#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_FileExplorer.h"
#include "BNS_PrimitiveCreation.h"
#include "BNS_Texture.h"

BNS_MultipleScene_UI::BNS_MultipleScene_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
{
}

BNS_MultipleScene_UI::~BNS_MultipleScene_UI()
{
}

void BNS_MultipleScene_UI::DrawUI()
{

	//DRAW HERE
	ImGui::Begin("Multiple Scene");

	static float padding = 16.0f;
	static float thumbnailSize = 128.0f;
	float cellSize = thumbnailSize + padding;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	ImGui::Columns(columnCount, 0, false);

	// creates an icon to the file
	TexturePtr icon = BNS_FileExplorer::GetInstance()->GetImageHashTable()["folder_icon"];

	for (int i = 0; i < 5; ++i)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::ImageButton((void*)icon.get()->GetShaderResourceView(),
			{ thumbnailSize, thumbnailSize }, { -1, 0 }, { 0,1 });

		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			//BNS_PrimitiveCreation::Instance()->CreateTexturedCube();
			if (i == 0)
				BNS_PrimitiveCreation::Instance()->CreatePlane();
			else if (i == 1)
				BNS_PrimitiveCreation::Instance()->CreateBunny();
			else if (i == 2)
				BNS_PrimitiveCreation::Instance()->CreateArmadillo();
			else if (i == 3)
				BNS_PrimitiveCreation::Instance()->CreateTeapot();
			else if (i == 4)
				BNS_PrimitiveCreation::Instance()->CreateEarth();
		}
		ImGui::PopStyleColor();
		ImGui::NextColumn();
	}
	ImGui::Columns(1);

	ImGui::End();
}
