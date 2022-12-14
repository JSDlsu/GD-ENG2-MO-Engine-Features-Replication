#pragma once
#include "BNS_AGameObject.h"
#include "BNS_EnumHandler.h"
#include "BNS_Prerequisites.h"
#include "BNS_StructHandler.h"

class BNS_AppWindow;

class BNS_Cube : public BNS_AGameObject
{
public:
	BNS_Cube(std::string name, BNS_ObjectTypes type);
	~BNS_Cube();
public:
	void Update(float deltaTime, BNS_AppWindow* app_window = nullptr) override;
	void Draw(const BlenderPtr& m_blender) override;
public:
	void SetMesh(const wchar_t* tex_path);
	void SetTexture(const wchar_t* tex_path, bool isNewLayer = true);
public:
	void SetVertex_Index_Buffer(BNS_VertexShaderType vs_type, BNS_PC_Cube_ColorData color_data = BNS_PC_Cube_ColorData());
	void SetVertexShader(BNS_VertexShaderType vs_type);
	void SetPixelShader(BNS_PixelShaderType ps_type);
protected:
	MeshPtr m_mesh;
	TexturePtr m_tex[10];
	int num_textures = 0;
	VertexBufferPtr m_vb;
	IndexBufferPtr m_ib;
protected:
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	BNS_VertexShaderType vs_type;
	BNS_PixelShaderType ps_type;
protected:
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float m_delta_time = 0.0f;
protected:
	friend class BNS_AppWindow;
};

