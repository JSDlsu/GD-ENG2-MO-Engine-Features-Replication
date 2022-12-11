#include "SceneWriter.h"
#include <iostream>
#include <fstream>

#include "Vector3D.h"
#include "BNS_GameObjectManager.h"

typedef std::fstream FileWriter;
SceneWriter::SceneWriter(std::string directory)
{
	this->directory = directory;
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::writeToFile()
{
	std::string fileDir = this->directory + ".iet";
	if (this->directory.find(".iet") != std::string::npos)
	{
		fileDir = this->directory;
	}

	FileWriter scenefile;
	scenefile.open(fileDir, std::ios::out);

	std::cout << "Selected filename " << fileDir << "\n";

	std::vector<BNS_AGameObject*> allObjects = BNS_GameObjectManager::get()->GetObjectList();

	for(int i = 0; i < allObjects.size(); i++)
	{
		scenefile << allObjects[i]->GetName() << std::endl;
		Vector3D position = allObjects[i]->GetLocalPosition();
		Vector3D rotation = allObjects[i]->GetLocalRotation();
		Vector3D scale = allObjects[i]->GetLocalScale();

		std::string type = "NONE";

		switch(allObjects[i]->ObjectType)
		{
			case BNS_ObjectTypes::CUBE:
			{
				type = "CUBE";
				break;
			}
			case BNS_ObjectTypes::PLANE:
			{
				type = "PLANE";
				break;
			}
			case BNS_ObjectTypes::CAMERA:
			{
				type = "CAMERA";
				break;
			}
			case BNS_ObjectTypes::MESH:
			{
				type = "MESH";
				break;
			}
			case BNS_ObjectTypes::SKYBOX:
			{
				type = "SKYBOX";
				break;
			}
		}

		scenefile << "Type: " << type << std::endl;
			scenefile << "Position: " << position.m_x << " " << position.m_y << " " << position.m_z << std::endl;
			scenefile << "Rotation: " << rotation.m_x << " " << rotation.m_y << " " << rotation.m_z << std::endl;
			scenefile << "Scale: " <<  scale.m_x <<" "<< scale.m_y <<" " << scale.m_z << std::endl;
	}
	scenefile.close();
}
