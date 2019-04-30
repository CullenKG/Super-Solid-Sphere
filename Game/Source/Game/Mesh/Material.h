#ifndef __Material_H__
#define __Material_H__

class ShaderProgram;

class Material
{
protected:
    ShaderProgram* m_pShader;
	MyColor m_Color;

	GLuint m_Texture;

	GLuint m_DiffuseTexture;
	GLuint m_SpecularTexture;
    GLuint m_NormalMapTexture;

	GLuint m_CubeMap;

	float m_Shininess;

public:
    Material() {}
	Material(ShaderProgram* pShader)
	{
		m_pShader = pShader;

		m_Texture = 0;
		m_Shininess = 0;
		m_DiffuseTexture = 0;
		m_SpecularTexture = 0;
		m_CubeMap = 0;
		m_Color = MyColor(0, 0, 0, 0);
	}

	Material(ShaderProgram* pShader, MyColor color)
	{
		m_pShader = pShader;
		m_Color = color;

		m_Texture = 0;
		m_Shininess = 0;
		m_DiffuseTexture = 0;
		m_SpecularTexture = 0;
		m_CubeMap = 0;
	}

	Material(ShaderProgram* pShader, GLuint texture)
	{
		m_pShader = pShader;
		m_Texture = texture;

		m_Shininess = 0;
		m_DiffuseTexture = 0;
		m_SpecularTexture = 0;
		m_CubeMap = 0;
		m_Color = MyColor(0, 0, 0, 0);
	}

	Material(ShaderProgram* pShader, GLuint texture, GLint cubemap)
	{
		m_pShader = pShader;
		m_Texture = texture;
		m_CubeMap = cubemap;

		m_Shininess = 0;
		m_DiffuseTexture = 0;
		m_SpecularTexture = 0;
		m_Color = MyColor(0, 0, 0, 0);
	}

	Material(ShaderProgram* pShader, MyColor color, float shininess)
	{
		m_pShader = pShader;
		m_Color = color;
		m_Shininess = shininess;

		m_Texture = 0;
		m_DiffuseTexture = 0;
		m_SpecularTexture = 0;
		m_CubeMap = 0;
	}

	Material(ShaderProgram* pShader, GLuint diffuseTexture, GLuint specularTexture, GLuint normalMapTexture, float shininess)
	{
		m_pShader = pShader;
		m_DiffuseTexture = diffuseTexture;
		m_SpecularTexture = specularTexture;
        m_NormalMapTexture = normalMapTexture;
		m_Shininess = shininess;

		m_Texture = 0;	
		m_CubeMap = 0;
		m_Color = MyColor(0, 0, 0, 0);
	}

	Material(ShaderProgram* pShader, GLuint diffuseTexture, GLuint specularTexture, GLuint normalMapTexture, GLuint cubeMap, float shininess)
	{
		m_pShader = pShader;
		m_DiffuseTexture = diffuseTexture;
		m_SpecularTexture = specularTexture;
		m_NormalMapTexture = normalMapTexture;
		m_CubeMap = cubeMap;
		m_Shininess = shininess;

		m_Texture = 0;
		m_Color = MyColor(0, 0, 0, 0);
	}


    ShaderProgram* GetShader() { return m_pShader; }
    MyColor GetColor() { return  m_Color; }
    GLuint GetTexture() { return  m_Texture; }
	GLuint GetDiffuseTexture() { return m_DiffuseTexture; }
	GLuint GetSpecularTexture() { return m_SpecularTexture; }
    GLuint GetNormalMapTexture() { return m_NormalMapTexture; }
	GLuint GetCubeMap() { return m_CubeMap; }
	float GetShininess() { return m_Shininess; }
};

#endif //__Material_H__
