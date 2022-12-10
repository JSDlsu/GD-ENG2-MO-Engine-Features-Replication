struct PS_INPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer BNS_constant_transform: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
	float4 m_camera_position;
	float4 m_light_position;
	float m_light_radius;
	float m_time;
	float alpha;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	//float t = (float)((sin((float)(m_time / (float)500.0f)) + 1.0f) / 2.0f);
	float t = 0.5f;
	return float4(lerp(input.color, input.color1, t), alpha);
}