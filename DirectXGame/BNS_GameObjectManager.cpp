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

std::vector<AGameObjectPtr>& BNS_GameObjectManager::GetObjectList()
{
	return objectList;
}

std::vector<AGameObjectPtr>& BNS_GameObjectManager::GetRenderObjectList()
{
	render_objectList = objectList;
	return render_objectList;
}


void BNS_GameObjectManager::deleteObject(AGameObjectPtr gameObject)
{
	
	int indexObjList = -1;
	int indexRenderList = -1;

	//DELETE AT OBJECT LIST
	for (int i = 0; i < this->objectList.size(); i++)
	{
		if (this->objectList[i] == gameObject)
		{
			indexObjList = i;
			break;
		}
	}

	

	//DELETE AT RENDER OBJECT LIST
	for (int i = 0; i < this->render_objectList.size(); i++)
	{
		if (this->render_objectList[i] == gameObject)
		{
			indexRenderList = i;
			break;
		}
	}
	 
	if (indexObjList != -1)
	{
		this->objectList.erase(this->objectList.begin() + indexObjList);
	}
	if (indexRenderList != -1)
	{
		this->render_objectList.erase(this->render_objectList.begin() + indexRenderList);
	}
	
	
	

	//gameObject.reset();
}

void BNS_GameObjectManager::deleteObjectByName(std::string name)
{
}



