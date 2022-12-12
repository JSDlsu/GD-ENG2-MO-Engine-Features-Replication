#pragma once
#include "Libs/RapidJson/include/rapidjson/document.h"
#include "Libs/RapidJson/include/rapidjson/stringbuffer.h"
#include "Libs/RapidJson/include/rapidjson/filereadstream.h"
#include "Libs/RapidJson/include/rapidjson/filewritestream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
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
	Document doc;

};

