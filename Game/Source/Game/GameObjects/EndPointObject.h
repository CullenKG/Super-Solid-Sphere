#ifndef __EndPointObject_H__
#define __EndPointObject_H__

class EndPointObject : public GameObject
{
protected:

public:
    EndPointObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    EndPointObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname);
    virtual ~EndPointObject();

    virtual void Update(float deltatime);

    virtual void Reset();
};

#endif //__EndPointObject_H__
