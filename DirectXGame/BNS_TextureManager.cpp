#include "BNS_TextureManager.h"
#include "BNS_Texture.h"


BNS_TextureManager::BNS_TextureManager() : BNS_ResourceManager()
{
}


BNS_TextureManager::~BNS_TextureManager()
{
}

TexturePtr BNS_TextureManager::createTextureFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<BNS_Texture>(createResourceFromFile(file_path));
}

BNS_Resource* BNS_TextureManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	BNS_Texture* tex = nullptr;
	try
	{
		tex = new BNS_Texture(file_path);
	}
	catch (...) {}

	return tex;
}