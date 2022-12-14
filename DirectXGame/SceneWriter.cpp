#include "SceneWriter.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <rapidjson/filewritestream.h>

#include "Vector3D.h"
#include "BNS_GameObjectManager.h"
#include "BNS_MenuToolbar_UI.h"

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
	Document d;

	std::vector<BNS_AGameObject*> allObjects = BNS_GameObjectManager::get()->GetObjectList();

	Value valChannel;
	int valSize = 0;
	valChannel.SetObject();
	{
		Value valTarget;
		Value myArray(kArrayType);
		valTarget.SetObject();
		for (valSize = 0; valSize < allObjects.size(); valSize++)
		{
			Value valObject;
			valObject.SetObject();
			{
				// for name
				Value tempName(allObjects[valSize]->GetName().c_str(), d.GetAllocator());
				valObject.AddMember("objectName", tempName, d.GetAllocator());
				// for type
				Value tempType(GetObjectType(allObjects[valSize]->ObjectType).c_str(), d.GetAllocator());
				//tempType.SetString(GenericValue<UTF8<>>::StringRefType(GetObjectType(allObjects[i]->ObjectType).c_str()));
				valObject.AddMember("objectType", tempType, d.GetAllocator());
				// for position
				Value valPos;
				valPos.SetObject();
				{
					valPos.AddMember("x", allObjects[valSize]->GetLocalPosition().m_x, d.GetAllocator());
					valPos.AddMember("y", allObjects[valSize]->GetLocalPosition().m_y, d.GetAllocator());
					valPos.AddMember("z", allObjects[valSize]->GetLocalPosition().m_z, d.GetAllocator());
				}
				valObject.AddMember("position", valPos, d.GetAllocator());// for rotation
				Value valRot;
				valRot.SetObject();
				{
					valRot.AddMember("x", allObjects[valSize]->GetLocalRotation().m_x, d.GetAllocator());
					valRot.AddMember("y", allObjects[valSize]->GetLocalRotation().m_y, d.GetAllocator());
					valRot.AddMember("z", allObjects[valSize]->GetLocalRotation().m_z, d.GetAllocator());
				}
				valObject.AddMember("rotation", valRot, d.GetAllocator());
				// for scale
				Value valScale;
				valScale.SetObject();
				{
					valScale.AddMember("x", allObjects[valSize]->GetLocalScale().m_x, d.GetAllocator());
					valScale.AddMember("y", allObjects[valSize]->GetLocalScale().m_y, d.GetAllocator());
					valScale.AddMember("z", allObjects[valSize]->GetLocalScale().m_z, d.GetAllocator());
				}
				valObject.AddMember("scale", valScale, d.GetAllocator());

				// for physics
				Value valPhys;
				BNS_AComponent* physics_comp = allObjects[valSize]->FindComponentOfType(ComponentType::Physics);
				valPhys.SetObject();
				{
					BNS_PhysicsComponent* physicsComp = dynamic_cast<BNS_PhysicsComponent*>(physics_comp);
					bool hasPhys = (physicsComp != nullptr) ? true : false;
					valPhys.AddMember("hasPhysics", hasPhys, d.GetAllocator());
					if (hasPhys == 1)
					{
						valPhys.AddMember("mass", (float)physicsComp->GetRigidBody()->getMass(), d.GetAllocator());
						valPhys.AddMember("bodyType", (int)physicsComp->GetRigidBody()->getType(), d.GetAllocator());
					}
					else if (hasPhys == 0)
					{
						valPhys.AddMember("mass", 0, d.GetAllocator());
						valPhys.AddMember("bodyType", -1, d.GetAllocator());
					}
				}
				valObject.AddMember("physicsComp", valPhys, d.GetAllocator());
			}
			myArray.PushBack(valObject, d.GetAllocator());
		}
		valTarget.AddMember("ObjectList", myArray, d.GetAllocator());
		valChannel.AddMember("BNS_FILE", valTarget, d.GetAllocator());
	}

	d.CopyFrom(valChannel, d.GetAllocator());

	/*
	// 2. Modify it by DOM.
	Value& s = d["stars"];
	s.SetInt(s.GetInt() + 1);
	*/
	std::string dir = BNS_MenuToolbar_UI::s_ScenePath.string() + "/output.json";
	FILE* fp = fopen(dir.c_str(), "wb"); // non-Windows use "w"

	// 3. Stringify the DOM
	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);
	d.Accept(writer);

	fclose(fp);
}

std::string SceneWriter::GetObjectType(BNS_ObjectTypes type)
{
	if (type == BNS_ObjectTypes::CUBE)
	{
		return "CUBE";
	}
	if (type == BNS_ObjectTypes::PLANE)
	{
		return "PLANE";
	}
	if (type == BNS_ObjectTypes::CAMERA)
	{
		return "CAMERA";
	}
	if (type == BNS_ObjectTypes::MESH)
	{
		return "MESH";
	}
	if (type == BNS_ObjectTypes::SKYBOX)
	{
		return "SKYBOX";
	}
	if (type == BNS_ObjectTypes::SPHERE)
	{
		return "SPHERE";
	}
	if (type == BNS_ObjectTypes::CAPSULE)
	{
		return "CAPSULE";
	}
	if (type == BNS_ObjectTypes::CYLINDER)
	{
		return "CYLINDER";
	}
}
