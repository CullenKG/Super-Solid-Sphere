#ifndef __GameObject_H__
#define __GameObject_H__

class ShaderProgram;
class Mesh;
class Scene;

class GameObject : public btMotionState
{
protected:
    Scene* m_pScene;

    unsigned int m_RenderOrder;

    std::string m_Name;

	vec3 m_InitialPosition;
	vec3 m_InitialRotation;
	vec3 m_InitialScale;

    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;

    Mesh* m_pMesh;
    Material* m_pMaterial;

    btRigidBody* m_pBody;

protected:
    virtual void getWorldTransform(btTransform& worldTrans) const;
    virtual void setWorldTransform(const btTransform& worldTrans);

public:
    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname);
    virtual ~GameObject();

    unsigned int GetRenderOrder() { return m_RenderOrder; }
    void SetRenderOrder(unsigned int order) { m_RenderOrder = order; }

    virtual void Init(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);

    virtual void Update(float deltatime);
    virtual void Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos);

	virtual void Reset();

    virtual void BeginContact(GameObject* other);

    void SetMesh(Mesh* pMesh) { m_pMesh = pMesh; }
    void SetMaterial(Material* pMaterial) { m_pMaterial = pMaterial; }

    Mesh* GetMesh() { return m_pMesh; }
    Material* GetMaterial() { return m_pMaterial; }

    void SetPosition(vec3 pos) { m_Position = pos; }
    void SetRotation(vec3 rot) { m_Rotation = rot; }
    void SetScale(vec3 scale) { m_Scale = scale; }

    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    vec3 GetScale()  { return m_Scale; }

    btRigidBody* GetPhysicsBody() { return m_pBody; }

    void CreateBoxBody(float mass, btCollisionObject::CollisionFlags flags = btCollisionObject::CollisionFlags::CF_STATIC_OBJECT);
    void CreateSphereBody(float mass, float radius, btCollisionObject::CollisionFlags flags = btCollisionObject::CollisionFlags::CF_STATIC_OBJECT);
};

#endif //__GameObject_H__
