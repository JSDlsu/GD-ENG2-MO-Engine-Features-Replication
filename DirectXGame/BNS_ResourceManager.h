#pragma once
#include <unordered_map>
#include <string>
#include "BNS_Prerequisites.h"

/* Abstract class
 * handles resources in such a way to simplify some very complex tasks such as
 * textures, static meshes, and materials.
 */
class BNS_ResourceManager
{
public:
	BNS_ResourceManager();
	virtual ~BNS_ResourceManager();

	ResourcePtr createResourceFromFile(const wchar_t* file_path);
protected:
	virtual BNS_Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;
private:
	// map for the path and the resource reference
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};

