#include "GamePCH.h"

int Mesh::FindSimilarVertexIndex(vec3 position, vec2 uv, vec3 normal, std::vector<vec3> &verticies, std::vector<vec2> &uvs, std::vector<vec3> &normals, int index)
{

	auto posIT = std::find(verticies.begin(), verticies.end(), position);
	auto uvIT = std::find(uvs.begin(), uvs.end(), uv);
	auto normalIT = std::find(normals.begin(), normals.end(), normal);

	int itIndex = posIT - verticies.begin();

	if (posIT != verticies.end() && uvIT != uvs.end() && normalIT != normals.end() && itIndex != index)
	{
		return itIndex;
	}

	return -1;
}

Mesh::Mesh()
{
	m_VBO = 0;
	m_IBO = 0;
	m_PrimitiveType = GL_TRIANGLES;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_IBO);
}

void Mesh::Init(VertexFormat* verts, int numverts, unsigned int* indices, int numindices, GLenum usage)
{
	m_NumVerts = numverts;
	m_NumIndices = numindices;

	// Generate and fill buffer with our vertex attributes.
	if (m_VBO == 0)
		glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat)*numverts, verts, usage);

	// Generate and fill buffer with our indices.
	if (m_IBO == 0)
		glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numindices, indices, usage);

	CheckForGLErrors();
}

void Mesh::Init(const void* verts, int numverts, int vertexbytesize, GLenum usage)
{
	m_NumVerts = numverts;
	m_NumIndices = 0;

	// Generate and fill buffer with our vertex attributes.
	if (m_VBO == 0)
		glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexbytesize, verts, usage);

	CheckForGLErrors();
}

void Mesh::SetupAttributes(ShaderProgram* pShaderProgram)
{
	assert(m_VBO != 0);

	// Bind our vertex and index buffers.
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	if (m_IBO != 0)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	GLuint programhandle = pShaderProgram->GetProgram();

	// Get the attribute locations.
	GLint aPos = glGetAttribLocation(programhandle, "a_Position");
	GLint aColor = glGetAttribLocation(programhandle, "a_Color");
	GLint aUV = glGetAttribLocation(programhandle, "a_UV");
	GLint aNormal = glGetAttribLocation(programhandle, "a_Normal");
	GLint aTangent = glGetAttribLocation(programhandle, "a_Tangent");

	// Setup our vbo and attributes.
	{
		// Setup the position attribute.
		assert(aPos != -1);
		glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, pos));
		glEnableVertexAttribArray(aPos);

		// Setup the color attribute.
		if (aColor != -1)
		{
			glVertexAttribPointer(aColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, color));
			glEnableVertexAttribArray(aColor);
		}

		// Setup the uv attribute.
		if (aUV != -1)
		{
			glVertexAttribPointer(aUV, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, uv));
			glEnableVertexAttribArray(aUV);
		}

		// Setup the normal attribute
		if (aNormal != -1)
		{
			glVertexAttribPointer(aNormal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, normal));
			glEnableVertexAttribArray(aNormal);
		}

		// Setup the tangent attribute
		if (aTangent != -1)
		{
			glVertexAttribPointer(aTangent, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, tangent));
			glEnableVertexAttribArray(aTangent);
		}
	}
}

void Mesh::SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos, const std::map<std::string, LightObject*> &lightObjects)
{
	ShaderProgram* pShaderProgram = pMaterial->GetShader();
	GLuint programhandle = pShaderProgram->GetProgram();

	// Enable our shader program.
	glUseProgram(programhandle);

	

	// Get the uniform locations.
	GLint uWorldMatrix = glGetUniformLocation(programhandle, "u_WorldMatrix");
	GLint uViewMatrix = glGetUniformLocation(programhandle, "u_ViewMatrix");
	GLint uProjMatrix = glGetUniformLocation(programhandle, "u_ProjMatrix");
	GLint uCameraPosition = glGetUniformLocation(programhandle, "u_CameraPosition");
	GLint uSkybox = glGetUniformLocation(programhandle, "u_Skybox");
	GLint uTexture = glGetUniformLocation(programhandle, "u_Texture");
	GLint uColor = glGetUniformLocation(programhandle, "u_Color");
	GLint uTime = glGetUniformLocation(programhandle, "u_Time");
	GLint uViewportSize = glGetUniformLocation(programhandle, "u_ViewportSize");
	GLint uViewportPosition = glGetUniformLocation(programhandle, "u_ViewportPosition");

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	if (uViewportPosition != -1)
	{
		glUniform2f(uViewportPosition, (float)viewport[0], (float)viewport[1]);
	}

	if (uViewportSize != -1)
	{
		glUniform2f(uViewportSize, (float)viewport[2], (float)viewport[3]);
	}

	// Get material uniform locations
	GLint uMaterialDiffuse = glGetUniformLocation(programhandle, "u_Material.diffuse");
	GLint uMaterialSpecular = glGetUniformLocation(programhandle, "u_Material.specular");
	GLint uMaterialNormalMap = glGetUniformLocation(programhandle, "u_Material.normal");
	GLint uMaterialColor = glGetUniformLocation(programhandle, "u_Material.color");
	GLint uMaterialShininess = glGetUniformLocation(programhandle, "u_Material.shininess");

	// Get textures
	GLuint diffuseTexture = pMaterial->GetDiffuseTexture();
	GLuint specularTexture = pMaterial->GetSpecularTexture();
	GLuint normalTexture = pMaterial->GetNormalMapTexture();
	MyColor color = pMaterial->GetColor();

	// Setup the material
	if (uMaterialDiffuse != -1)
	{
		// Diffuse texture
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture);
		glUniform1i(uMaterialDiffuse, 1);
	}

	if (uMaterialSpecular != -1)
	{
		// Specular texture
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, specularTexture);
		glUniform1i(uMaterialSpecular, 2);
	}

	if (uMaterialNormalMap != -1)
	{
		// Normal map texture
		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(GL_TEXTURE_2D, normalTexture);
		glUniform1i(uMaterialNormalMap, 3);
	}

	if (uMaterialColor != -1)
	{
		// Color
		glUniform3f(uMaterialColor, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	}

	if (uMaterialShininess != -1)
	{
		// Shininess
		glUniform1f(uMaterialShininess, pMaterial->GetShininess());
	}

	// Get the directional light uniform locations
	GLint uDirectionalLightDirection = glGetUniformLocation(programhandle, "u_DirectionalLight.direction");
	GLint uDirectionalLightAmbient = glGetUniformLocation(programhandle, "u_DirectionalLight.ambient");
	GLint uDirectionalLightDiffuse = glGetUniformLocation(programhandle, "u_DirectionalLight.diffuse");
	GLint uDirectionalLightSpecular = glGetUniformLocation(programhandle, "u_DirectionalLight.specular");

	// Setup the directional light
	if (uDirectionalLightDirection != -1 && uDirectionalLightAmbient != -1 && uDirectionalLightDiffuse != -1 && uDirectionalLightSpecular != -1)
	{
		// Get the directional light from the scene
		for (auto light : lightObjects)
		{
			DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(light.second);

			if (directionalLight != nullptr)
			{
				// Light direction
				glUniform3f(uDirectionalLightDirection, directionalLight->GetDirection().x, directionalLight->GetDirection().y, directionalLight->GetDirection().z);

				// Ambient light color
				glUniform3f(uDirectionalLightAmbient, directionalLight->GetAmbientColor().x, directionalLight->GetAmbientColor().y, directionalLight->GetAmbientColor().z);

				// Diffuse light color
				glUniform3f(uDirectionalLightDiffuse, directionalLight->GetDiffuseColor().x, directionalLight->GetDiffuseColor().y, directionalLight->GetDiffuseColor().z);

				// Specular light color
				glUniform3f(uDirectionalLightSpecular, directionalLight->GetSpecularColor().x, directionalLight->GetSpecularColor().y, directionalLight->GetSpecularColor().z);

				break;
			}
		}
	}

	// Point lights
	{
		int numberOfPointLights = 0;

		// Loop through all the lights in the scene
		for (auto light : lightObjects)
		{
			PointLight* pointLight = dynamic_cast<PointLight*>(light.second);

			if (pointLight != nullptr)
			{
				std::string index = std::to_string(numberOfPointLights);

				// Get the uniform locations
				GLint uPointLightPosition = glGetUniformLocation(programhandle, ("u_PointLights[" + index + "].position").c_str());
				GLint uPointLightAmbient = glGetUniformLocation(programhandle, ("u_PointLights[" + index + "].ambient").c_str());
				GLint uPointLightDiffuse = glGetUniformLocation(programhandle, ("u_PointLights[" + index + "].diffuse").c_str());
				GLint uPointLightSpecular = glGetUniformLocation(programhandle, ("u_PointLights[" + index + "].specular").c_str());
				GLint uPointLightLinear = glGetUniformLocation(programhandle, ("u_PointLights[" + index + "].linear").c_str());
				GLint uPointLightConstant = glGetUniformLocation(programhandle, ("u_PointLights[" + index + "].constant").c_str());
				GLint uPointLightQuadratic = glGetUniformLocation(programhandle, ("u_PointLights[" + index + "].quadratic").c_str());

				if (uPointLightPosition != -1)
					glUniform3f(uPointLightPosition, pointLight->GetPosition().x, pointLight->GetPosition().y, pointLight->GetPosition().z);
				if (uPointLightAmbient != -1)
					glUniform3f(uPointLightAmbient, pointLight->GetAmbientColor().x, pointLight->GetAmbientColor().y, pointLight->GetAmbientColor().z);
				if (uPointLightDiffuse != -1)
					glUniform3f(uPointLightDiffuse, pointLight->GetDiffuseColor().x, pointLight->GetDiffuseColor().y, pointLight->GetDiffuseColor().z);
				if (uPointLightSpecular != -1)
					glUniform3f(uPointLightSpecular, pointLight->GetSpecularColor().x, pointLight->GetSpecularColor().y, pointLight->GetSpecularColor().z);
				if (uPointLightLinear != -1)
					glUniform1f(uPointLightLinear, pointLight->GetLinear());
				if (uPointLightConstant != -1)
					glUniform1f(uPointLightConstant, pointLight->GetConstant());
				if (uPointLightQuadratic != -1)
					glUniform1f(uPointLightQuadratic, pointLight->GetQuadratic());

				numberOfPointLights++;
			}
		}

		// Get number of lights uniform location
		GLint uNumberOfPointLights = glGetUniformLocation(programhandle, "u_NumberOfPointLights");

		if (uNumberOfPointLights != -1)
		{
			glUniform1i(uNumberOfPointLights, numberOfPointLights);
		}
	}

	// Setup the texture.
	GLuint texturehandle = pMaterial->GetTexture();
	if (texturehandle != 0 && uTexture != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 4);
		glBindTexture(GL_TEXTURE_2D, texturehandle);
		glUniform1i(uTexture, 4);
	}

	GLuint texturehandlecube = pMaterial->GetCubeMap();
	if (texturehandlecube != 0 && uSkybox != -1)
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, texturehandlecube);
		glUniform1i(uSkybox, 0);
	}

	if (uWorldMatrix != -1)
	{
		glUniformMatrix4fv(uWorldMatrix, 1, false, &pMatWorld->m11);
	}

	if (uViewMatrix != -1)
	{
		glUniformMatrix4fv(uViewMatrix, 1, false, &pMatView->m11);
	}

	if (uProjMatrix != -1)
	{
		glUniformMatrix4fv(uProjMatrix, 1, false, &pMatProj->m11);
	}

	if (uCameraPosition != -1)
	{
		glUniform3f(uCameraPosition, campos.x, campos.y, campos.z);
	}

	// Setup time.
	if (uTime != -1)
	{
		glUniform1f(uTime, (float)GetSystemTime());
	}

	CheckForGLErrors();
}

void Mesh::SetupUniform1f(ShaderProgram * pShader, std::string uniform, float value)
{
	GLuint programhandle = pShader->GetProgram();

	glUseProgram(programhandle);

	GLint uUniform = glGetUniformLocation(programhandle, uniform.c_str());

	if (uUniform != -1)
	{
		glUniform1f(uUniform, value);
	}

	CheckForGLErrors();
}

void Mesh::Draw(ShaderProgram* pShaderProgram)
{
	GLuint programhandle = pShaderProgram->GetProgram();

	// Draw the shape.
	if (m_NumIndices > 0)
	{
		glDrawElements(m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(m_PrimitiveType, 0, m_NumVerts);
	}

	GLint aPos = glGetAttribLocation(programhandle, "a_Position");
	GLint aColor = glGetAttribLocation(programhandle, "a_Color");
	GLint aUV = glGetAttribLocation(programhandle, "a_UV");
	GLint aNormal = glGetAttribLocation(programhandle, "a_Normal");

	// Disable the attribute arrays used
	glDisableVertexAttribArray(aPos);

	if (aColor != -1)
		glDisableVertexAttribArray(aColor);

	if (aUV != -1)
		glDisableVertexAttribArray(aUV);

	if (aNormal != -1)
		glDisableVertexAttribArray(aNormal);

	CheckForGLErrors();
}
