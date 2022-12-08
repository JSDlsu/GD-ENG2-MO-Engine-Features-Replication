#pragma once
#include <string>
class SceneReader
{
public:
	SceneReader(std::string directory);
	~SceneReader();
	void readFromFile();
	std::string directory;
};

