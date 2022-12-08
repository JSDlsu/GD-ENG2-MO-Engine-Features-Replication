/*#include "SceneReader.h"
#include "BNS_Cube.h"
#include "BNS_GameObjectManager.h"
//#include "StringUtils.h"

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
	//BNS_GameObjectManager::primitive type
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;

	while(std::getline(sceneFile,readLine))
	{
		if(index==0)
		{
			objectName = readLine;
			index++;
		}
		else if (index == 1)
		{
			//std::vector stringSplit = StringUtils::split(readLine,'');
			//objecttype = (AGameObject::PrimitiveType) std::stoi(stringSplit[1]);
			index++;
		}
		else if (index == 2)
		{
			//std::vector stringSplit = StringUtils::split(readLine,'');
			//position = Vector3D(std::stof(stringSplit[1], std::stoi(stringSplit[2]),  std::stoi(stringSplit[3]));
			index;;
		}
		else if (index == 3)
		{
			//std::vector stringSplit = StringUtils::split(readLine,'');
			//rotation = Vector3D(std::stof(stringSplit[1], std::stoi(stringSplit[2]),  std::stoi(stringSplit[3]));
			index++;
		}
		else if (index == 4)
		{
			//std::vector stringSplit = StringUtils::split(readLine,'');
			//scale = Vector3D(std::stof(stringSplit[1], std::stoi(stringSplit[2]),  std::stoi(stringSplit[3]));
			index = 0;

			const char* name = "cube";
			BNS_Cube* cube = new BNS_Cube(name, BNS_ObjectTypes::CUBE);
			cube->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
			cube->SetVertexShader(BNS_VertexShaderType::COLOR);
			cube->SetPixelShader(BNS_PixelShaderType::COLOR);
			cube->SetPosition(position);
			cube->SetRotation(rotation);
			cube->SetScale(scale);


		}
	}
}*/
