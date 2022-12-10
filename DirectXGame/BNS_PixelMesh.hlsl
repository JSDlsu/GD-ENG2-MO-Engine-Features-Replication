Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
};

cbuffer BNS_constant_transform: register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;
	float4 m_light_direction;
	float4 m_camera_position;
	float m_time;
	float alpha;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
	float3 pixelColor = Texture.Sample(TextureSampler,input.texcoord * 0.5f);
	//return Texture.Sample(TextureSampler, input.texcoord);
	return float4(pixelColor, alpha);
}