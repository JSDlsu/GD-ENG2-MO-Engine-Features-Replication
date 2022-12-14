#include "BNS_ContentBrowser_UI.h"

#include "BNS_Cube.h"
#include "BNS_FileExplorer.h"
#include "BNS_Hierarchy_UI.h"
#include "BNS_PrimitiveCreation.h"
#include "BNS_Texture.h"

std::filesystem::path const BNS_ContentBrowser_UI::s_AssetPath = "Assets";

BNS_ContentBrowser_UI::BNS_ContentBrowser_UI(std::string name, int ID) : BNS_AUIScreen(name, ID)
{
	m_CurrentDirectory = s_AssetPath;
}

BNS_ContentBrowser_UI::~BNS_ContentBrowser_UI()
{
}

void BNS_ContentBrowser_UI::DrawUI()
{
	std::string windowLabel = name + "##" + std::to_string(ID);
	ImGui::Begin(windowLabel.c_str());
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
		ImGui::ImageButton((void*)icon.get()->GetShaderResourceView(), 
			{ thumbnailSize, thumbnailSize }, { -1, 0}, { 0,1 });
		ImGui::PopStyleColor();

		// selection functionality
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			//if selection is a folder
			if (directory_entry.is_directory())
			{
				m_CurrentDirectory /= path.filename();
			}
			//if selection is a object file
			else if (IsObject(filenameString))
			{
				BNS_PrimitiveCreation::Instance()->CreateMeshFromFile(path.string(), filenameString);
			}
			//if selection is a texture file
			else if (IsTexture(filenameString))
			{
				BNS_Hierarchy_UI* uiTemp = dynamic_cast<BNS_Hierarchy_UI*>(BNS_UIManager::GetInstance()->GetUIHashTable()[BNS_UINames::HIERARCHY_SCREEN].get());
				std::string tempPathString = path.string();
				std::wstring tempPath = std::wstring(tempPathString.begin(), tempPathString.end());
				LPCWSTR convertedFilepath = tempPath.c_str();
				dynamic_cast<BNS_Cube*>(uiTemp->GetSelectedGO())->SetVertex_Index_Buffer(BNS_VertexShaderType::TEXTURE);
				dynamic_cast<BNS_Cube*>(uiTemp->GetSelectedGO())->SetVertexShader(BNS_VertexShaderType::TEXTURE);
				dynamic_cast<BNS_Cube*>(uiTemp->GetSelectedGO())->SetPixelShader(BNS_PixelShaderType::TEXTURE);
				dynamic_cast<BNS_Cube*>(uiTemp->GetSelectedGO())->SetTexture(convertedFilepath, false);
				
				std::cout << "Seleceted GO: " << dynamic_cast<BNS_Cube*>(uiTemp->GetSelectedGO())->GetName()
				<< "\nSelected Texture: " << path.string() << std::endl;
			}

				
		}
		ImGui::TextWrapped(filenameString.c_str());

		ImGui::NextColumn();
	}

	ImGui::Columns(1);
	// sliders for adjusting content browser
	ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
	ImGui::SliderFloat("Padding", &padding, 0, 32);


	ImGui::End();
}

bool BNS_ContentBrowser_UI::IsObject(std::string filenameString)
{
	//get the file extension for 3 LETTER WORD EXTENSIONS (works for opening obj files)
	std::string fileExtension = filenameString.substr(filenameString.find('.') + 1, 3);
	if (fileExtension == "obj")
	{
		return true;
	}
	return false;
}

bool BNS_ContentBrowser_UI::IsTexture(std::string filenameString)
{
	//get the file extension for 3 LETTER WORD EXTENSIONS (works for opening obj files)
	std::string fileExtension = filenameString.substr(filenameString.find('.') + 1, 3);


	BNS_Hierarchy_UI* uiTemp = dynamic_cast<BNS_Hierarchy_UI*>(BNS_UIManager::GetInstance()->GetUIHashTable()[BNS_UINames::HIERARCHY_SCREEN].get());
	BNS_AGameObject* go = dynamic_cast<BNS_Cube*>(uiTemp->GetSelectedGO());

	if (go != nullptr && (fileExtension == "jpg" || fileExtension == "png"))
	{
		return true;
	}
	return false;
}
