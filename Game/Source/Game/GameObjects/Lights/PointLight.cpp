#include "GamePCH.h"

PointLight::PointLight(Scene* pScene, std::string name, vec3 pos, float constant, float linear, float quadratic) : LightObject(pScene, name, pos, vec3(0)),
	m_Constant(constant),
	m_Linear(linear),
	m_Quadratic(quadratic)
{
}

PointLight::~PointLight()
{
}

float PointLight::GetConstant()
{
	return m_Constant;
}

float PointLight::GetLinear()
{
	return m_Linear;
}

float PointLight::GetQuadratic()
{
	return m_Quadratic;
}
