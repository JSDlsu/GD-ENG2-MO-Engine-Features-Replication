#pragma once
#include "AGameObject.h"
#include "EnumHandler.h"
#include "Prerequisites.h"
#include "StructHandler.h"

class AppWindow;

class Cube : public AGameObject
{
public:
	Cube(std::string name, ObjectTypes type);
	~Cube();
public:
	void Update(float deltaTime, AppWindow* app_window) override;
	void Draw(const BlenderPtr& m_blender) override;
public:
	void SetMesh(const wchar_t* tex_path);
	void SetTexture(const wchar_t* tex_path);
public:
	void SetVertex_Index_Buffer(VertexShaderType vs_type, PC_Cube_ColorData color_data = PC_Cube_ColorData());
	void SetVertexShader(VertexShaderType vs_type);
	void SetPixelShader(PixelShaderType ps_type);
public:
	void SetAlpha(float alpha);
	float GetAlpha();
protected:
	MeshPtr m_mesh;
	TexturePtr m_tex;
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
	ConstantBufferPtr m_cb;
	ConstantBufferPtr m_cb_texture;
protected:
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	VertexShaderType vs_type;
	PixelShaderType ps_type;
protected:
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float deltaTime = 0.0f;
	float alpha = 1.0f;
protected:
	friend class AppWindow;
};

