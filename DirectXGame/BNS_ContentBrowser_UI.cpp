#include "BNS_ContentBrowser_UI.h"

#include "BNS_FileExplorer.h"
#include "BNS_Texture.h"

std::filesystem::path const BNS_ContentBrowser_UI::s_AssetPath = "Assets";

BNS_ContentBrowser_UI::BNS_ContentBrowser_UI(std::string name) : BNS_AUIScreen(name)
{
	m_CurrentDirectory = s_AssetPath;
}

BNS_ContentBrowser_UI::~BNS_ContentBrowser_UI()
{
}

void BNS_ContentBrowser_UI::DrawUI()
{
	ImGui::Begin("Content Browser");

	// Check if the current path leaves the source path, which will add a back button
	if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
	{
		if (ImGui::Button("<-"))
		{
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
	}

	static float padding = 16.0f;
	static float thumbnailSize = 128.0f;
	float cellSize = thumbnailSize + padding;

	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	ImGui::Columns(columnCount, 0, false);

	// iterate all of the files inside the folder path
	for (auto& directory_entry : std::filesystem::directory_iterator(m_CurrentDirectory))
	{
		const auto& path = directory_entry.path();
		auto relativePath = std::filesystem::relative(path, s_AssetPath);
		std::string filenameString = relativePath.filename().string();

		// creates an icon to the file
		TexturePtr icon = directory_entry.is_directory() ? 
			BNS_FileExplorer::GetInstance()->GetImageHashTable()["folder_icon"] :
			BNS_FileExplorer::GetInstance()->GetImageHashTable()["file_icon"];
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
		ImGui::ImageButton((void*)icon.get()->GetShaderResourceView(), { thumbnailSize, thumbnailSize }, { -1, 0}, { 0,1 });
		ImGui::PopStyleColor();

		// selection functionality
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			if (directory_entry.is_directory())
			{
				m_CurrentDirectory /= path.filename();
			}
		}
		ImGui::TextWrapped(filenameString.c_str());

		ImGui::NextColumn();
	}

	ImGui::Columns(1);

	ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
	ImGui::SliderFloat("Padding", &padding, 0, 32);


	ImGui::End();
}
