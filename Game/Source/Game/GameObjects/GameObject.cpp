#include "GamePCH.h"



GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
{
    Init(pScene, name, pos, rot, scale, pMesh, pMaterial);
}

GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname)
{
    ResourceManager* pResources = pScene->GetResourceManager();
    Init(pScene, name, pos, rot, scale, pResources->GetMesh(meshname), pResources->GetMaterial(materialname));
}

GameObject::~GameObject()
{
    if (m_pBody)
    {
        m_pScene->GetBulletWorld()->GetDynamicsWorld()->removeRigidBody(m_pBody);
        delete m_pBody;
    }
}

void GameObject::Init(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
{
    m_pScene = pScene;

    m_RenderOrder = 1;

    m_Name = name;

	m_InitialPosition = pos;
	m_InitialRotation = rot;
	m_InitialScale = scale;

    m_Position = pos;
    m_Rotation = rot;
    m_Scale = scale;

    m_pMesh = pMesh;
    m_pMaterial = pMaterial;

    m_pBody = 0;
}

void GameObject::Update(float deltatime)
{
}

void GameObject::Draw(int renderorder, mat4* pMatView, mat4* pMatProj, vec3 campos)
{
    if (m_pMesh == 0)
        return;

    ShaderProgram* pShaderProgram = m_pMaterial->GetShader();

    mat4 world;
    world.CreateSRT(m_Scale, m_Rotation, m_Position);

    m_pMesh->SetupAttributes(pShaderProgram);
    m_pMesh->SetupUniforms(m_pMaterial, &world, pMatView, pMatProj, campos, m_pScene->GetAllLightsInScene());
    m_pMesh->Draw(pShaderProgram);
}

void GameObject::Reset()
{
	if (m_pBody)
	{
		m_pBody->clearForces();

		btVector3 zeroVector(0, 0, 0);
		m_pBody->setLinearVelocity(zeroVector);
		m_pBody->setAngularVelocity(zeroVector);

		vec3 diff = m_InitialPosition - m_Position;
		m_pBody->translate(btVector3(diff.x, diff.y, diff.z));
	}
	
	m_Position = m_InitialPosition;
	m_Rotation = m_InitialRotation;
	m_Scale = m_InitialScale;
}

void GameObject::BeginContact(GameObject * other)
{
}

void GameObject::CreateBoxBody(float mass, btCollisionObject::CollisionFlags flags)
{
    btCollisionShape* colShape = 0;

#undef new
    colShape = new btBoxShape(btVector3(1.0f / 2, 1.0f / 2, 1.0f / 2));
    colShape->setLocalScaling(btVector3(m_Scale.x, m_Scale.y, m_Scale.z));

    btVector3 localInertia;
    colShape->calculateLocalInertia(mass, localInertia);

    m_pScene->GetBulletWorld()->AddShape(colShape);

    btRigidBody::btRigidBodyConstructionInfo btInfo(mass, this, colShape, localInertia);

    m_pBody = new btRigidBody(btInfo);

    m_pBody->setUserPointer(this);
    m_pBody->setCollisionFlags(m_pBody->getCollisionFlags() | flags);

    m_pScene->GetBulletWorld()->GetDynamicsWorld()->addRigidBody(m_pBody);
}

void GameObject::CreateSphereBody(float mass, float radius, btCollisionObject::CollisionFlags flags)
{
    btCollisionShape* colShape = 0;

#undef new
    colShape = new btSphereShape(btScalar(radius));

    btVector3 localInertia;
    colShape->calculateLocalInertia(mass, localInertia);

    m_pScene->GetBulletWorld()->AddShape(colShape);

    btRigidBody::btRigidBodyConstructionInfo btInfo(mass, this, colShape, localInertia);

    m_pBody = new btRigidBody(btInfo);

    m_pBody->setUserPointer(this);
    m_pBody->setCollisionFlags(m_pBody->getCollisionFlags() | flags);

    m_pScene->GetBulletWorld()->GetDynamicsWorld()->addRigidBody(m_pBody);
}

void GameObject::getWorldTransform(btTransform & worldTrans) const
{
    worldTrans.setOrigin(btVector3(m_Position.x, m_Position.y, m_Position.z));
    worldTrans.setRotation(btQuaternion(m_Rotation.y / 180.0f * PI, m_Rotation.x / 180.0f * PI, m_Rotation.z / 180.0f * PI));
}

void GameObject::setWorldTransform(const btTransform & worldTrans)
{
    mat4 bulletMatrix;
    worldTrans.getOpenGLMatrix(&bulletMatrix.m11);

    m_Rotation = bulletMatrix.GetEulerAngles() / PI * 180.0f;
    m_Position = bulletMatrix.GetTranslation();
}