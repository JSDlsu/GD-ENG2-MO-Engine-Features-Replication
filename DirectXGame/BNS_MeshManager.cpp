#include "BNS_MeshManager.h"
#include "BNS_Mesh.h"

BNS_MeshManager::BNS_MeshManager()
{
}


BNS_MeshManager::~BNS_MeshManager()
{
}

MeshPtr BNS_MeshManager::createMeshFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<BNS_Mesh>(createResourceFromFile(file_path));
}

BNS_Resource* BNS_MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	BNS_Mesh* mesh = nullptr;
	try
	{
		mesh = new BNS_Mesh(file_path);
	}
	catch (...) {}

	return mesh;
}