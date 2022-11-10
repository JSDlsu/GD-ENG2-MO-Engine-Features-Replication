#pragma once

enum class BNS_ObjectTypes
{
	CUBE = 0,
	MESH,
	PLANE,
	CAMERA
};

enum class BNS_VertexShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP
};

enum class BNS_PixelShaderType
{
	TEXTURE = 0,
	MESH,
	COLOR,
	COLOR_LERP
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
	CREDITS_SCREEN,
	SCENEVIEW_SCREEN,
	CONTENT_BROWSER_SCREEN,
	GAMEOBJECT_SCREEN,
	CONSOLE_SCREEN
};

class BNS_EnumHandler
{
	
};