#pragma once
#include "BNS_EnumHandler.h"
#include "Libs/RapidJson/include/rapidjson/document.h"
#include "Libs/RapidJson/include/rapidjson/stringbuffer.h"
#include "Libs/RapidJson/include/rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <iostream>
#include <vector>

using namespace rapidjson;

class SceneReader
{
public:
	SceneReader(std::string directory);
	~SceneReader();
	void readFromFile();
	std::string directory;

public:
	void parseJson(std::string JSONpath);
	Value& getSheet(std::string mainKey);
	GenericArray<false, rapidjson::Value> getSheetArr(std::string mainKey,
		std::string key);
	std::vector<std::string> returnProperties();
private:
	BNS_ObjectTypes GetObjectType(std::string type);
private:
	Document doc;

};

