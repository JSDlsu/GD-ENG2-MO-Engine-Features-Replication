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

		std::string ObjectType = "NONE";
		std::string BodyType = "NONE";

		switch(allObjects[i]->ObjectType)
		{
			case BNS_ObjectTypes::CUBE:
			{
				ObjectType = "CUBE";
				break;
			}
			case BNS_ObjectTypes::PLANE:
			{
				ObjectType = "PLANE";
				break;
			}
			case BNS_ObjectTypes::CAMERA:
			{
				ObjectType = "CAMERA";
				break;
			}
			case BNS_ObjectTypes::MESH:
			{
				ObjectType = "MESH";
				break;
			}
			case BNS_ObjectTypes::SKYBOX:
			{
				ObjectType = "SKYBOX";
				break;
			}
		}

		scenefile << "Type: " << ObjectType << std::endl;
		scenefile << "Position: " << position.m_x << " " << position.m_y << " " << position.m_z << std::endl;
		scenefile << "Rotation: " << rotation.m_x << " " << rotation.m_y << " " << rotation.m_z << std::endl;
		scenefile << "Scale: " <<  scale.m_x <<" "<< scale.m_y <<" " << scale.m_z << std::endl;


		BNS_AComponent* physics_comp = allObjects[i]->FindComponentOfType(ComponentType::Physics);
		if (physics_comp != nullptr)
		{
			BNS_PhysicsComponent* physicsComp = dynamic_cast<BNS_PhysicsComponent*>(physics_comp);
			scenefile << "Physics: " << 1 << std::endl;
			scenefile << "Mass: " << (float)physicsComp->GetRigidBody()->getMass() << std::endl;
			scenefile << "BodyType: " << (int)physicsComp->GetRigidBody()->getType() << std::endl;
		}
	}
	scenefile.close();
}

void SceneWriter::WriteJSON()
{
	char cbuf[1024]; rapidjson::MemoryPoolAllocator<> allocator(cbuf, sizeof cbuf);
	rapidjson::Document meta(&allocator, 256);
	meta.SetObject();
	meta.AddMember("foo", 123, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	meta.Accept(writer);
	std::string json(buffer.GetString(), buffer.GetSize());

	std::ofstream of("/tmp/example.json");
	of << json;
	if (!of.good()) throw std::runtime_error("Can't write the JSON string to the file!");
}
