#ifndef __DirectionalLight_H__
#define __DirectionalLight_H__

class DirectionalLight : public LightObject
{
public:
	DirectionalLight(Scene* pScene, std::string name, vec3 pos, vec3 direction);
	~DirectionalLight();

	vec3 GetDirection();

protected:
	vec3 m_Direction;
};

#endif __DirectionalLight_H__
