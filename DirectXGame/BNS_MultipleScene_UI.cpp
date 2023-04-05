#include "BNS_MultipleScene_UI.h"
#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_FileExplorer.h"
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
			std::cout << "Button# " << i << std::endl;
		}
		ImGui::PopStyleColor();
		ImGui::NextColumn();
	}
	ImGui::Columns(1);
	// sliders for adjusting content browser
	ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
	ImGui::SliderFloat("Padding", &padding, 0, 32);

	ImGui::End();
}
