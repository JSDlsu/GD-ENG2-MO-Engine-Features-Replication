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
	BNS_ObjectTypes ObjectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	bool hasPhysics;
	float mass;
	BodyType BodyType;

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
				ObjectType = BNS_ObjectTypes::CUBE;
			if (stringSplit[1] == "PLANE")
				ObjectType = BNS_ObjectTypes::PLANE;

			
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
			index++;

			
			
		}

		else if (index == 5)
		{
			std::vector stringSplit = BNS_StringUtils::split(readLine, ' ');
			if (std::stoi(stringSplit[1]) == 0)
			{
				index = 0;
				BNS_PrimitiveCreation::Instance()->createPrimitiveFromFile(objectName, ObjectType, position, rotation, scale);
			}
			else if (std::stoi(stringSplit[1]) == 1)
			{
				hasPhysics = true;
				index++;
			}
		}

		else if (index == 6)
		{
			std::vector stringSplit = BNS_StringUtils::split(readLine, ' ');
			mass = std::stof(stringSplit[1]);
			index++;
		}

		else if (index == 7)
		{
			std::vector stringSplit = BNS_StringUtils::split(readLine, ' ');

			if (stringSplit[1] == "STATIC")
				BodyType = BodyType::STATIC;
			else if (stringSplit[1] == "KINEMATIC")
				BodyType = BodyType::KINEMATIC;
			else if (stringSplit[1] == "DYNAMIC")
				BodyType = BodyType::DYNAMIC;

			index = 0;

			BNS_PrimitiveCreation::Instance()->createPrimitiveFromFile(objectName, ObjectType, position, rotation, scale, hasPhysics, mass, BodyType);
		}
	}
}
