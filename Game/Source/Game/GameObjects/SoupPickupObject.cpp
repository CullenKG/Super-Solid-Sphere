#include "GamePCH.h"

SoupPickupObject::SoupPickupObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial) : 
    GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_HasBeenPickedUp = false;
}

SoupPickupObject::SoupPickupObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname) :
    GameObject(pScene, name, pos, rot, scale, meshname, materialname)
{
    m_HasBeenPickedUp = false;
}

SoupPickupObject::~SoupPickupObject()
{
}

void SoupPickupObject::Update(float deltatime)
{
}

void SoupPickupObject::Reset()
{
}
