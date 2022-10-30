struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
};

cbuffer constant_transform: register(b0)
{
	row_major float4x4 m_world;
	row_major  float4x4 m_view;
	row_major float4x4 m_proj;
	unsigned int m_time;
};

cbuffer constant_texture: register(b0)
{
	float alpha;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	return float4(input.color,1.0f);
}