#pragma once
#include "ResourceManager.h"

/*
 * handles the creation of reference for mesh resources.
 * Calls the instantiate a ‘Mesh’ object and returns it
 * through its function. 
 */
class MeshManager : public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	MeshPtr createMeshFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};