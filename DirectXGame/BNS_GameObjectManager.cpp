#include "BNS_GameObjectManager.h"

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
