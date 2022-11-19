#pragma once
#include <string>
#include <vector>
#include "BNS_Prerequisites.h"

class BNS_AppWindow;
/*
 * stores the created object in the scene;
 * use to access the draw function for each
 * objects in the scene.
 */
class BNS_GameObjectManager
{
public:
	BNS_GameObjectManager();
	~BNS_GameObjectManager();

public:
	static BNS_GameObjectManager* get();
	static void create();
	static void release();
	std::vector<AGameObjectPtr>& GetObjectList();
	std::vector<AGameObjectPtr>& GetRenderObjectList();
	void deleteObject(AGameObjectPtr gameObject);
	void deleteObjectByName(std::string name);

private:
	std::vector<AGameObjectPtr> objectList;
	std::vector<AGameObjectPtr> render_objectList;
	static BNS_GameObjectManager* m_instance;
	friend class BNS_AppWindow;
	friend class BNS_Cube;
};
