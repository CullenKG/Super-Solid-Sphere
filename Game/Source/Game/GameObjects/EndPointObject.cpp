#include "GamePCH.h"

EndPointObject::EndPointObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial) :
    GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
}

EndPointObject::EndPointObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname) :
    GameObject(pScene, name, pos, rot, scale, meshname, materialname)
{
}

EndPointObject::~EndPointObject()
{
}

void EndPointObject::Update(float deltatime)
{
}

void EndPointObject::Reset()
{
}
