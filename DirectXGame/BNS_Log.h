#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <unordered_map>

#include "BNS_EnumHandler.h"

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_win32.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "BNS_UI_Prerequisites.h"

class BNS_Log
{
public:

	BNS_Log();
	~BNS_Log();

	static BNS_Log* GetInstance();
	static void create();
	static void release();

	ImGuiTextBuffer textBuffer;
	ImGuiTextFilter textFilter;
	ImVector<int> lineOffsets;
	bool scrollToBottom;

	typedef enum
	{
		Display = 0,
		Warning = 1,
		Error = 2
	} LogVerbosity;

	void Clear()
	{
		textBuffer.clear();
		lineOffsets.clear();
	}

	void WriteLog(LPCSTR callingFunc, LogVerbosity verbosity, std::string message)
	{
		/*
		if (verbosity == LogVerbosity::Display)
		{
			std::string format = "Display: " + std::string(callingFunc) + "|||||  " + message + "\n";
			ImGui::TextColored(ImVec4(0, 1, 0, 1), format.c_str());

		}


		else if (verbosity == LogVerbosity::Warning)
		{
			std::string format = "Warning: " + std::string(callingFunc) + "|||||  " + message + "\n";
			ImGui::TextColored(ImVec4(1, 1, 0, 1), format.c_str());
		}

		else
		{
			std::string format = "Error: " + std::string(callingFunc) + "|||||  " + message + "\n";
			ImGui::TextColored(ImVec4(1, 0, 0, 1), format.c_str());
		}
		*/
	}

	void WriteLog(const char* fmt, LogVerbosity verbosity, ...) IM_FMTARGS(2)
	{
		va_list args;
		va_start(args, fmt);
		textBuffer.append(enum_to_string(verbosity).c_str());
		textBuffer.append(": ");
		textBuffer.appendfv(fmt, args);
		textBuffer.append("\n");
		va_end(args);
		scrollToBottom = true;
		
	}

	void Draw()
	{
		ImGui::Text(textBuffer.begin());
		if (scrollToBottom)
			ImGui::SetScrollHereY(1.0f);
		scrollToBottom = false;
		
	}

private:
	static BNS_Log* m_instance;

	std::string enum_to_string(LogVerbosity verbosity);

};