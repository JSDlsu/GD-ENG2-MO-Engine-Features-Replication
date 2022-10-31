#include "AppWindow.h"
#include "InputSystem.h"
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "PrimitiveCreation.h"
#include "ShaderEngine.h"
#include "RenderBufferEngine.h"

int main()
{
	try
	{
		// initialize our GraphicsEngine
		GraphicsEngine::create();
		// initialize our ShaderEngine
		ShaderEngine::create();
		// initialize our ShaderEngine
		RenderBufferEngine::create();
		// initialize our InputSystem
		InputSystem::create();
		// initialize our GameObjectManager
		GameObjectManager::create();
		// initialize our PrimitiveCreation
		PrimitiveCreation::create();
	}
	catch (...) { return -1; }
	{
		try
		{
			AppWindow app;
			while (app.isRun());
		}
		catch (...) {
			PrimitiveCreation::release();
			GameObjectManager::release();
			InputSystem::release();
			RenderBufferEngine::release();
			ShaderEngine::release();
			GraphicsEngine::release();
			return -1;
		}
	}

	/* NOTE:
	 * The order of release should be based on the order of creation.
	 * Will follow the First in, Last out principle.
	 */
	PrimitiveCreation::release();
	GameObjectManager::release();
	InputSystem::release();
	RenderBufferEngine::release();
	ShaderEngine::release();
	GraphicsEngine::release();

	return 0;
}
