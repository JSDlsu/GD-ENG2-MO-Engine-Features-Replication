#pragma once
#include <string>
#include <vector>

#include "BNS_AGameObject.h"
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
	std::vector<BNS_AGameObject*>& GetObjectList();
	std::vector<BNS_AGameObject*>& GetRenderObjectList();
	void DeleteObject(BNS_AGameObject* gameObject);
	void DeleteObjectByName(std::string name);

private:
	std::vector<BNS_AGameObject*> objectList;
	std::vector<BNS_AGameObject*> render_objectList;
	static BNS_GameObjectManager* m_instance;
	friend class BNS_AppWindow;
	friend class BNS_Cube;
};
