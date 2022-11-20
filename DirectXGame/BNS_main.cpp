#include "BNS_AppWindow.h"
#include "BNS_InputSystem.h"
#include "BNS_GameObjectManager.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_PrimitiveCreation.h"
#include "BNS_ShaderEngine.h"
#include "BNS_RenderBufferEngine.h"
#include "BNS_Log.h"

int main()
{
	try
	{
		// initialize our BNS_GraphicsEngine
		BNS_GraphicsEngine::create();
		// initialize our BNS_ShaderEngine
		BNS_ShaderEngine::create();
		// initialize our BNS_ShaderEngine
		BNS_RenderBufferEngine::create();
		// initialize our BNS_InputSystem
		BNS_InputSystem::create();
		// initialize our BNS_GameObjectManager
		BNS_GameObjectManager::create();
		// initialize our BNS_PrimitiveCreation
		BNS_PrimitiveCreation::create();
		// initialize our BNS_Log
		BNS_Log::create();
	}
	catch (...) { return -1; }
	{
		try
		{
			BNS_AppWindow app;
			while (app.isRun());
		}
		catch (...) {
			BNS_Log::release();
			BNS_PrimitiveCreation::release();
			BNS_GameObjectManager::release();
			BNS_InputSystem::release();
			BNS_RenderBufferEngine::release();
			BNS_ShaderEngine::release();
			BNS_GraphicsEngine::release();
			return -1;
		}
	}

	/* NOTE:
	 * The order of release should be based on the order of creation.
	 * Will follow the First in, Last out principle.
	 */
	BNS_Log::release();
	BNS_PrimitiveCreation::release();
	BNS_GameObjectManager::release();
	BNS_InputSystem::release();
	BNS_RenderBufferEngine::release();
	BNS_ShaderEngine::release();
	BNS_GraphicsEngine::release();

	return 0;
}
