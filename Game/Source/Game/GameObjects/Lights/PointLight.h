#ifndef __PointLight_H__
#define __PointLight_H__

class PointLight : public LightObject
{
public:
    PointLight(Scene* pScene, std::string name, vec3 pos, float constant, float linear, float quadratic);
    ~PointLight();

	float GetConstant();
	float GetLinear();
	float GetQuadratic();

protected:
    float m_Constant;
    float m_Linear;
    float m_Quadratic;
};

#endif __PointLight_H__
