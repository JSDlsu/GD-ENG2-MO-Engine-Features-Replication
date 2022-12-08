#include "BNS_GameObjectManager.h"

#include "BNS_AGameObject.h"

BNS_GameObjectManager* BNS_GameObjectManager::m_instance = nullptr;

BNS_GameObjectManager::BNS_GameObjectManager()
{
}

BNS_GameObjectManager::~BNS_GameObjectManager()
{
}

BNS_GameObjectManager* BNS_GameObjectManager::get()
{
	return m_instance;
}

void BNS_GameObjectManager::create()
{
	if (BNS_GameObjectManager::m_instance)
		throw std::exception("BNS_GameObjectManager already created");
	BNS_GameObjectManager::m_instance = new BNS_GameObjectManager();
}

void BNS_GameObjectManager::release()
{
	if (!BNS_GameObjectManager::m_instance)
		return;
	delete BNS_GameObjectManager::m_instance;
}

std::vector<BNS_AGameObject*>& BNS_GameObjectManager::GetObjectList()
{
	return objectList;
}

std::vector<BNS_AGameObject*>& BNS_GameObjectManager::GetRenderObjectList()
{
	render_objectList = objectList;
	return render_objectList;
}


void BNS_GameObjectManager::DeleteObject(BNS_AGameObject* gameObject)
{
	int indexObjList = -1;
	int indexRenderList = -1;

	// DELETE AT OBJECT LIST
	for (int i = 0; i < objectList.size(); i++)
	{
		if (objectList[i] == gameObject)
		{
			indexObjList = i;
			delete objectList[i];
			break;
		}
	}
	
	for (int i = 0; i < render_objectList.size(); i++)
	{
		if (render_objectList[i] == gameObject)
		{
			indexRenderList = i;
			break;
		}
	}

	if (indexObjList != -1)
	{
		objectList.erase(objectList.begin() + indexObjList);
	}
	if (indexRenderList != -1)
	{
		render_objectList.erase(render_objectList.begin() + indexRenderList);
	}

}

void BNS_GameObjectManager::DeleteObjectByName(std::string name)
{
}

void BNS_GameObjectManager::SetSkyBox(BNS_SkyBox* skybox)
{
	current_SkyBox = skybox;
}

BNS_SkyBox* BNS_GameObjectManager::GetSkyBox()
{
	return current_SkyBox;
}



