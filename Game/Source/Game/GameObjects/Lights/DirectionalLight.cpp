#include "GamePCH.h"

DirectionalLight::DirectionalLight(Scene * pScene, std::string name, vec3 pos, vec3 direction) : LightObject(pScene, name, pos, vec3(0)),
	m_Direction(direction)
{
}

DirectionalLight::~DirectionalLight()
{
}

vec3 DirectionalLight::GetDirection()
{
	return m_Direction;
}
