Texture2D Texture: register(t0);
sampler TextureSampler: register(s0);

struct PS_INPUT
{
	float4 position: SV_POSITION;
	float2 texcoord: TEXCOORD0;
	float3 normal: NORMAL0;
	float3 direction_to_camera: TEXCOORD1;
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
	// ambient reflection
	float ka = 0.1f;
	// ambient light color
	float3 ia = float3(1.0f, 1.0f, 1.0f);
	// product of ambient reflection and light color
	float3 ambient_light = ka * ia;

	// diffuse reflection
	float kd = 0.7;
	// diffuse light color
	float3 id = float3(1.0f, 1.0f, 1.0f);
	// dot product
	float amount_diffuse_light = max(0.0f, dot(m_light_direction.xyz, input.normal));
	//float amount_diffuse_light = max(0.0f, dot(float3(0.0f, 0.0f, 1.0f), input.normal));

	float3 diffuse_light = kd * amount_diffuse_light * id;

	// SPECULAR LIGHT
	float ks = 1.0f;
	// specular color
	float3 is = float3(1.0f, 1.0f, 1.0f);
	float3 reflected_light = reflect(m_light_direction.xyz, input.normal);
	//float3 reflected_light = reflect(float3(0.0f, 0.0f, 1.0f), input.normal);
	float shininess = 100.0f;
	float amount_specular_light = pow(max(0.0f, dot(reflected_light, input.direction_to_camera)), shininess);

	float specular_light = ks * amount_specular_light * is;

	float3 final_light = ambient_light + diffuse_light + specular_light;

	float3 pixelColor = Texture.Sample(TextureSampler,input.texcoord * 0.5f);
	//return float4(pixelColor, alpha);
	return float4(final_light, alpha);
}