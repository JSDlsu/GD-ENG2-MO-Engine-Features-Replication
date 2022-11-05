#pragma once
#include "BNS_ResourceManager.h"

/*
 * Handles the creation of reference for texture resources
 */
class BNS_TextureManager : public BNS_ResourceManager
{
public:
	BNS_TextureManager();
	~BNS_TextureManager();
	TexturePtr createTextureFromFile(const wchar_t* file_path);
protected:
	virtual BNS_Resource* createResourceFromFileConcrete(const wchar_t* file_path);
};
