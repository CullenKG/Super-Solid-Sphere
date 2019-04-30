#include "GamePCH.h"

LightObject::LightObject(Scene* pScene, std::string name, vec3 pos, vec3 rot) : GameObject(pScene, name, pos, rot, vec3(1), 0, 0)
{
    
}

LightObject::~LightObject()
{
}

void LightObject::SetLightColor(vec3 ambientColor, vec3 diffuseColor, vec3 specularColor)
{
	m_AmbientColor = ambientColor;
	m_DiffuseColor = diffuseColor;
	m_SpecularColor = specularColor;
}

vec3 LightObject::GetAmbientColor()
{
    return m_AmbientColor;
}

vec3 LightObject::GetDiffuseColor()
{
    return m_DiffuseColor;
}

vec3 LightObject::GetSpecularColor()
{
    return m_SpecularColor;
}
