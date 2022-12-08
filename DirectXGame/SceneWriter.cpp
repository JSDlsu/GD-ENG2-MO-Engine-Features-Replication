/*#include "SceneWriter.h"
#include <iostream>
#include <fstream>

#include "Vector3D.h"


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

	GameObjectManager::List allObjects = GameObjectManager::getInstance()->getAllObjects();

	for(int i = 0; i < allObjects.size(); i++)
	{
		scenefile << allObjects[i]->getName() << std::end;
		Vector3D position = allObjects[i]->getLocalPosition();
		Vector3D rotation = allObjects[i]->getLocalRotation();
		Vector3D scale = allObjects[i]->getLocalScale();

		scenefile << "Type:" << allObjects[i]->getObjectType() << std::endl;
			scenefile << "Position:" << position.getX() << " " << position.getY() << " " << position.getZ() << std::endl;
			scenefile << "Rotation:" << rotation.getX() << " " << rotation.getY() << " " << rotation.getZ() << std::endl;
			scenefile << "Scale:" <<  scale.getX() <<" "<< scale.getY()<<" " << scale.getZ() << std::endl;
	}
	scenefile.close();
}*/
