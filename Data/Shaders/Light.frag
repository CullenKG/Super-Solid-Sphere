// Camera position
uniform vec3 u_CameraPosition;

// Directional light
uniform DirectionalLight u_DirectionalLight;

// Number of point lights
uniform int u_NumberOfPointLights;

// Point lights
uniform PointLight u_PointLights[32];

// Material
uniform Material u_Material;

varying mat4 v_WorldMat;
varying vec4 v_WorldPos;
varying vec3 v_Normal;
varying vec2 v_UV;

void main()
{
	// Set the normals back to their proper direction
	mat3 normalMatrix = transpose(inverse(mat3(v_WorldMat)));
	vec3 normal = normalize(normalMatrix * v_Normal);

	// Get the direction to the camera
	vec3 directionToCamera = normalize(u_CameraPosition - v_WorldPos.xyz);

	// Calculate lighting from the directional light
	//vec3 colorAfterLighting = CalculateDirectionalLightColor(u_DirectionalLight, u_Material, v_UV, normal, directionToCamera);

	// Calculate lighting from point lights
	for (int i = 0; i < u_NumberOfPointLights; i++)
	{
		//colorAfterLighting += CalculatePointLightColor(u_PointLights[i], u_Material, v_UV, normal, v_WorldPos.xyz, directionToCamera);
	}

	// Set final color
	//gl_FragColor = vec4(colorAfterLighting, 1);
}
