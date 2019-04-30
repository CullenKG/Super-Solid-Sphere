#ifndef __LightObject_H__
#define __LightObject_H__

class LightObject : public GameObject
{
public:
    LightObject(Scene* pScene, std::string name, vec3 pos, vec3 rot);
    ~LightObject();

    void SetLightColor(vec3 ambientColor, vec3 diffuseColor, vec3 specularColor);

    vec3 GetAmbientColor();
    vec3 GetDiffuseColor();
    vec3 GetSpecularColor();

protected:
    vec3 m_AmbientColor;
    vec3 m_DiffuseColor;
    vec3 m_SpecularColor;
};

#endif __LightObject_H__
