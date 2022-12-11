#include "SceneReader.h"
#include "BNS_Cube.h"
#include "BNS_GameObjectManager.h"
#include "BNS_PrimitiveCreation.h"
#include "BNS_StringUtils.h"

typedef std::fstream FileReader;
SceneReader::SceneReader(std::string directory)
{
	this->directory = directory;
}

SceneReader::~SceneReader()
{
}

void SceneReader::readFromFile()
{
	std::string fileDir = this->directory + ".iet";
	if(this->directory.find(".iet")!= std::string::npos)
	{
		fileDir = this->directory;
	}

	FileReader sceneFile;
	sceneFile.open(fileDir, std::ios::in);

	int index = 0;
	std::string readLine;

	std::string objectName;
	BNS_ObjectTypes type;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	while(std::getline(sceneFile,readLine))
	{
		if(index == 0)
		{
			objectName = readLine;
			index++;
		}
		else if (index == 1)
		{
			std::vector stringSplit = BNS_StringUtils::split(readLine,' ');
			

			if (stringSplit[1] == "CUBE")
				type = BNS_ObjectTypes::CUBE;
			if (stringSplit[1] == "PLANE")
				type = BNS_ObjectTypes::PLANE;

			
			index++;
		}
		else if (index == 2)
		{
			std::vector stringSplit = BNS_StringUtils::split(readLine,' ');
			position = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]),  std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 3)
		{
			std::vector stringSplit = BNS_StringUtils::split(readLine,' ');
			rotation = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]),  std::stof(stringSplit[3]));
			index++;
		}
		else if (index == 4)
		{
			std::vector stringSplit = BNS_StringUtils::split(readLine,' ');
			scale = Vector3D(std::stof(stringSplit[1]), std::stof(stringSplit[2]),  std::stof(stringSplit[3]));
			index = 0;

			BNS_PrimitiveCreation::Instance()->createPrimitiveFromFile(objectName, type, position, rotation, scale);
		}
	}
}
