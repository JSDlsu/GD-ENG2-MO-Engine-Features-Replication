#include "SceneReader.h"
#include "BNS_Cube.h"
#include "BNS_GameObjectManager.h"
#include "BNS_MenuToolbar_UI.h"
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
	//CHANGE THE CONCATENATED EXPORTED SCENE TO FILENAME TO IMPORT
	std::string importedFileExt = "/output";
	std::string dir = BNS_MenuToolbar_UI::s_ScenePath.string() + importedFileExt;
	parseJson(dir);

	std::string objectName;
	BNS_ObjectTypes ObjectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	bool hasPhysics = false;
	float mass = 0;
	int BodyType = 0;
	
		Value& attributes = getSheet("BNS_FILE")["ObjectList"];
		//assert(attributes.IsArray()); // attributes is an array
		for (Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
			const Value& attribute = *itr;
			assert(attribute.IsObject()); // each attribute is an object
			objectName = attribute["objectName"].GetString();
			ObjectType = GetObjectType(attribute["objectType"].GetString());
			position = Vector3D(attribute["position"]["x"].GetFloat(),
				attribute["position"]["y"].GetFloat(),
				attribute["position"]["z"].GetFloat());
			rotation = Vector3D(attribute["rotation"]["x"].GetFloat(),
				attribute["rotation"]["y"].GetFloat(),
				attribute["rotation"]["z"].GetFloat());
			scale = Vector3D(attribute["scale"]["x"].GetFloat(),
				attribute["scale"]["y"].GetFloat(),
				attribute["scale"]["z"].GetFloat());
			hasPhysics = attribute["physicsComp"]["hasPhysics"].GetBool();
			mass = attribute["physicsComp"]["mass"].GetDouble();
			BodyType = attribute["physicsComp"]["bodyType"].GetInt();
			BNS_PrimitiveCreation::Instance()->createPrimitiveFromFile(objectName, ObjectType, position, rotation, scale, hasPhysics, mass, BodyType);
		}

}


void SceneReader::parseJson(std::string JSONpath)
{
	//1
	JSONpath += ".json";
	FILE* file = fopen(JSONpath.c_str(), "rb");
	assert(file != 0);
	//2
	char readBuffer[65536];
	FileReadStream is(file, readBuffer, sizeof(readBuffer));
	//3
	this->doc.ParseStream(is);
	fclose(file);
}

Value& SceneReader::getSheet(std::string mainKey)
{
	Value& player = this->doc[mainKey.c_str()];
	return player; //player["name"].GetString()/GetInt();
}

GenericArray<false, Value> SceneReader::getSheetArr(std::string mainKey, std::string key)
{
	GenericArray<false, Value> items = getSheet(mainKey)[key.c_str()].GetArray();
	return items; //items[i].GetFloat();
}

std::vector<std::string> SceneReader::returnProperties()
{
	std::vector<std::string> sample;
	for (Value::ConstMemberIterator itr = doc["frames"].MemberBegin();
		itr != doc["frames"].MemberEnd(); ++itr)
	{
		sample.push_back(itr->name.GetString());
	}
	return sample;
}

BNS_ObjectTypes SceneReader::GetObjectType(std::string type)
{

	std::cout << "type: " << type << std::endl;
	if (type.compare("CUBE") == 0)
	{
		return BNS_ObjectTypes::CUBE;
	}
	if (type.compare("PLANE") == 0)
	{
		return BNS_ObjectTypes::PLANE;
	}
	if (type.compare("CAMERA") == 0)
	{
		return BNS_ObjectTypes::CAMERA;
	}
	if (type.compare("MESH") == 0)
	{
		return BNS_ObjectTypes::MESH;
	}
	if (type.compare("SKYBOX") == 0)
	{
		return BNS_ObjectTypes::SKYBOX;
	}
	if (type.compare("SPHERE") == 0)
	{
		return BNS_ObjectTypes::SPHERE;
	}
	if (type.compare("CAPSULE") == 0)
	{
		return BNS_ObjectTypes::CAPSULE;
	}
	if (type.compare("CYLINDER") == 0)
	{
		return BNS_ObjectTypes::CYLINDER;
	}
}
