#pragma once
#include <vector>
#include "BNS_Prerequisites.h"

class BNS_AppWindow;
/*
 * stores the created object in the scene;
 * use to access the draw function for each
 * objects in the scene.
 */
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

public:
	static GameObjectManager* get();
	static void create();
	static void release();
	std::vector<AGameObjectPtr>& getObjectList();
	
private:
	std::vector<AGameObjectPtr> objectList;
	static GameObjectManager* m_instance;
	friend class BNS_AppWindow;
	friend class Cube;
};
