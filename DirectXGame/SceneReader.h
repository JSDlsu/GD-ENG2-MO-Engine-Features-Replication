#pragma once
#include "Libs/RapidJson/include/rapidjson/document.h"
#include "Libs/RapidJson/include/rapidjson/stringbuffer.h"
#include "Libs/RapidJson/include/rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <vector>


class SceneReader
{
public:
	SceneReader(std::string directory);
	~SceneReader();
	void readFromFile();
	std::string directory;

public:
	void parseJson(std::string JSONpath);
	rapidjson::Value& getSheet(std::string mainKey);
	rapidjson::GenericArray<false, rapidjson::Value> getSheetArr(std::string mainKey,
		std::string key);
	std::vector<std::string> returnProperties();
private:
	rapidjson::Document doc;

};

