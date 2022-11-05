#pragma once
#include "BNS_ResourceManager.h"

/*
 * handles the creation of reference for _mesh resources.
 * Calls the instantiate a ‘BNS_Mesh’ object and returns it
 * through its function. 
 */
class BNS_MeshManager : public BNS_ResourceManager
{
public:
	BNS_MeshManager();
	~BNS_MeshManager();
	MeshPtr createMeshFromFile(const wchar_t* file_path);
protected:
	virtual BNS_Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};