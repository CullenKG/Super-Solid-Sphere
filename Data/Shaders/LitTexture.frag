// Directional light
uniform DirectionalLight u_DirectionalLight;

// Number of point lights
uniform int u_NumberOfPointLights;

// Point lights
uniform PointLight u_PointLights[32];

// Material
uniform TexturedMaterial u_Material;

varying mat3 v_TBN;

varying vec3 v_CameraPosition;
varying vec3 v_ObjectPosition;
varying vec2 v_UV;

void main()
{
	vec3 normal = texture2D(u_Material.normal, v_UV).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	normal = normalize(v_TBN * normal);

	// Get the direction to the camera
	vec3 viewDirection = normalize(v_CameraPosition - v_ObjectPosition);

	// Get the objects color
	vec3 diffuseColor = texture2D(u_Material.diffuse, v_UV).xyz;
	vec3 specularColor = texture2D(u_Material.specular, v_UV).xyz;

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