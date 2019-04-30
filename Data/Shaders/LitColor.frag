// Directional light
uniform DirectionalLight u_DirectionalLight;

// Number of point lights
uniform int u_NumberOfPointLights;

// Point lights
uniform PointLight u_PointLights[32];

// Material
uniform ColoredMaterial u_Material;

varying mat3 v_NormalMatrix;
varying vec3 v_Normal;
varying vec3 v_CameraPosition;
varying vec3 v_ObjectPosition;
varying vec2 v_UV;

void main()
{
	//vec3 normal = v_NormalMatrix * vec3(0, 1, 0);

	vec3 normal = normalize(v_NormalMatrix * v_Normal);

	// Get the direction to the camera
	vec3 viewDirection = normalize(v_CameraPosition - v_ObjectPosition);

	// Get the objects color
	vec3 diffuseColor = u_Material.color;
	vec3 specularColor = u_Material.color;

	vec3 result = vec3(0.0, 0.0, 0.0);

	// Calculate lighting from the directional light
	result += CalculateDirectionalLightColor(u_DirectionalLight, diffuseColor, specularColor, normal, viewDirection, u_Material.shininess);

	// Calculate lighting from point lights

	for (int i = 0; i < u_NumberOfPointLights; i++)
	{
		result += CalculatePointLightColor(u_PointLights[i], diffuseColor, specularColor, normal, v_ObjectPosition, viewDirection, u_Material.shininess);
	}

	// Set final color
	gl_FragColor = vec4(result, 1);
}