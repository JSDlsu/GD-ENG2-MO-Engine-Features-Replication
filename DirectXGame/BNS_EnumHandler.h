#pragma once

enum class BNS_ObjectTypes
{
	CUBE = 0,
	MESH,
	PLANE,
	CAMERA,
	SKYBOX
};

enum class BNS_VertexShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP,
	LIGHTING
};

enum class BNS_PixelShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP,
	LIGHTING,
	SKYBOX
};

enum class BNS_InputLayoutType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP
};

enum class BNS_UINames
{
	PROFILER_SCREEN,
	MENU_SCREEN,
	INSPECTOR_SCREEN,
	HIERARCHY_SCREEN,
	SCENEVIEW_SCREEN,
	CONTENT_BROWSER_SCREEN,
	GAMEOBJECT_SCREEN,
	CONSOLE_SCREEN
};

enum class ComponentType
{
	NotSet = -1,
	Script,
	Renderer,
	Input,
	Physics,
	Transform
};

//DEPRECATED
enum class LogType
{
	Display = 0,
	Warning,
	Error
};

class BNS_EnumHandler
{
	
};