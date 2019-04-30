#ifndef __SoupPickupObject_H__
#define __SoupPickupObject_H__

class SoupPickupObject : public GameObject
{
protected:
    bool m_HasBeenPickedUp;

public:
    SoupPickupObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    SoupPickupObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname);
    virtual ~SoupPickupObject();

    virtual void Update(float deltatime);

    virtual void Reset();
};

#endif //__SoupPickupObject_H__
