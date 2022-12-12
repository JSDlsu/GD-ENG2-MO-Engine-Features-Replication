#pragma once
#include <fstream>
#include <string>
#include "Libs/RapidJson/include/rapidjson/document.h"
#include "Libs/RapidJson/include/rapidjson/stringbuffer.h"
#include "Libs/RapidJson/include/rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class SceneWriter
{
public:
	SceneWriter(std::string directory);
	~SceneWriter();
	void writeToFile();
	std::string directory;

public:
	void WriteJSON();
};

