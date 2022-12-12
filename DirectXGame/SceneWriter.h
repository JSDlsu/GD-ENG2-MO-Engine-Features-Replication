#pragma once
#include <fstream>
#include <string>

#include "BNS_EnumHandler.h"
#include "Libs/RapidJson/include/rapidjson/document.h"
#include "Libs/RapidJson/include/rapidjson/stringbuffer.h"
#include "Libs/RapidJson/include/rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

class SceneWriter
{
public:
	SceneWriter(std::string directory);
	~SceneWriter();
	void writeToFile();
	std::string directory;

public:
	std::string GetObjectType(BNS_ObjectTypes type);
	
};

