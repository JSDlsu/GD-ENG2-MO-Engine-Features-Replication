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
	std::string dir = BNS_MenuToolbar_UI::s_ScenePath.string() + "/output";
	parseJson(dir);

	std::string objectName;
	BNS_ObjectTypes ObjectType;
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	bool hasPhysics = false;
	float mass = 0;
	int BodyType = 0;

	int objects_size = getSheet("Objects_Size").GetInt();

	for (int i = 0; i < objects_size; ++i)
	{
		objectName = getSheet("BNS_FILE")[std::to_string(i).c_str()]["objectName"].GetString();
		ObjectType = GetObjectType(getSheet("BNS_FILE")[std::to_string(i).c_str()]["objectType"].GetString());
		position = Vector3D(getSheet("BNS_FILE")[std::to_string(i).c_str()]["position"]["x"].GetFloat(),
			getSheet("BNS_FILE")[std::to_string(i).c_str()]["position"]["y"].GetFloat(),
			getSheet("BNS_FILE")[std::to_string(i).c_str()]["position"]["z"].GetFloat());
		rotation = Vector3D(getSheet("BNS_FILE")[std::to_string(i).c_str()]["rotation"]["x"].GetFloat(),
			getSheet("BNS_FILE")[std::to_string(i).c_str()]["rotation"]["y"].GetFloat(),
			getSheet("BNS_FILE")[std::to_string(i).c_str()]["rotation"]["z"].GetFloat());
		scale = Vector3D(getSheet("BNS_FILE")[std::to_string(i).c_str()]["scale"]["x"].GetFloat(),
			getSheet("BNS_FILE")[std::to_string(i).c_str()]["scale"]["y"].GetFloat(),
			getSheet("BNS_FILE")[std::to_string(i).c_str()]["scale"]["z"].GetFloat());
		hasPhysics = getSheet("BNS_FILE")[std::to_string(i).c_str()]["physicsComp"]["hasPhysics"].GetBool();
		mass = getSheet("BNS_FILE")[std::to_string(i).c_str()]["physicsComp"]["mass"].GetDouble();
		BodyType = getSheet("BNS_FILE")[std::to_string(i).c_str()]["physicsComp"]["bodyType"].GetInt();
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
		return BNS_ObjectTypes::SKYBOX;;
	}
	if (type.compare("SPHERE") == 0)
	{
		return BNS_ObjectTypes::SPHERE;
	}
}
