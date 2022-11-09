#include "BNS_ContentBrowser_UI.h"

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

	if (m_CurrentDirectory != std::filesystem::path(s_AssetPath))
	{
		if (ImGui::Button("<-"))
		{
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
	}

	for (auto& directory_entry : std::filesystem::directory_iterator(m_CurrentDirectory))
	{
		const auto& path = directory_entry.path();
		auto relativePath = std::filesystem::relative(path, s_AssetPath);
		std::string filenameString = relativePath.filename().string();
		if (directory_entry.is_directory())
		{
			if (ImGui::Button(filenameString.c_str()))
			{
				m_CurrentDirectory /= path.filename();
			}
		}
		else
		{
			if (ImGui::Button(filenameString.c_str()))
			{

			}
		}
	}


	ImGui::End();
}
