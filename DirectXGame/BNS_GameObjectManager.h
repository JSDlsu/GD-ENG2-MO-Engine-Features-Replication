#pragma once
#include <string>
#include <vector>

#include "BNS_AGameObject.h"
#include "BNS_Prerequisites.h"
#include "BNS_EditorAction.h"

class BNS_SkyBox;
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
public:
	std::vector<BNS_AGameObject*>& GetObjectList();
	std::vector<BNS_AGameObject*>& GetRenderObjectList();

public:
	void DeleteObject(BNS_AGameObject* gameObject);
	void DeleteObjectByName(std::string name);
	BNS_AGameObject* FindObject(BNS_AGameObject* gameObject);
	BNS_AGameObject* FindObjectByName(std::string name);

public:
	void saveEditStates();
	void restoreEditStates();
	void applyEditorAction(BNS_EditorAction* action);

public:
	void SetSkyBox(BNS_SkyBox* skybox);
	BNS_SkyBox* GetSkyBox();

private:
	std::vector<BNS_AGameObject*> objectList;
	std::vector<BNS_AGameObject*> render_objectList;
	BNS_SkyBox* current_SkyBox = nullptr;
	static BNS_GameObjectManager* m_instance;
	friend class BNS_AppWindow;
	friend class BNS_Cube;
};
