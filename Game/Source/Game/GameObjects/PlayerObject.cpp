#include "GamePCH.h"

PlayerObject::PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
    : GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
    m_pController = 0;
    m_InputDirection = vec2(0);
	m_MovementDirection = vec2(0, 1);
	m_PureInputDirection = vec2(0);
	m_pSoundPlayer = new SoundPlayer();


    m_BeatLevel = false;
}

PlayerObject::PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname)
    : GameObject(pScene, name, pos, rot, scale, meshname, materialname)
{
    m_pController = 0;
	m_InputDirection = vec2(0);
	m_MovementDirection = vec2(0, 1);
	m_PureInputDirection = vec2(0);
	m_pSoundPlayer = new SoundPlayer();

    m_BeatLevel = false;

}

PlayerObject::~PlayerObject()
{
	delete m_pSoundPlayer;
}

void PlayerObject::SetController(PlayerController* pController)
{
    m_pController = pController;

    if (m_pBody)
    {
        m_pBody->setActivationState(DISABLE_DEACTIVATION);
    }
}

vec2 PlayerObject::GetInputDirection()
{
    return m_InputDirection;
}

vec2 PlayerObject::GetMovementDirection()
{
	return m_MovementDirection;
}

void PlayerObject::BeginContact(GameObject * other)
{
    EndPointObject* endpoint = dynamic_cast<EndPointObject*>(other);

    if (endpoint != nullptr)
    {
        m_BeatLevel = true;
    }
}

void PlayerObject::Update(float deltatime)
{
    GameObject::Update(deltatime);

    if (m_pScene->GetOption("Texture") == true)
    {
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("Snow");
    }
    if (m_pScene->GetOption("Texture") == false)
    {
        m_pMaterial = m_pScene->GetResourceManager()->GetMaterial("Crystal");
    }

	CameraObject* pCamera = (CameraObject*)m_pScene->GetGameObject("Camera");

	Vector3 forwardDir = pCamera->GetForwardDirection();
	forwardDir.y = 0.0f;
	forwardDir.Normalize();

	Vector3 rightDir = pCamera->GetRightDirection();
	rightDir.y = 0.0f;
	rightDir.Normalize();

    if (m_pController == 0)
        return;

    vec3 dir(0, 0, 0);
	m_PureInputDirection = vec2(0);

	if (m_pController->IsButtonHeld(PCB_Up))
	{
		m_PureInputDirection.y += 1;
		dir += forwardDir;
	}
	if (m_pController->IsButtonHeld(PCB_Down))
	{
		m_PureInputDirection.y -= 1;
		dir -= forwardDir;
	}
		
	if (m_pController->IsButtonHeld(PCB_Left))
	{
		m_PureInputDirection.x -= 1;
		dir -= rightDir;
	}
	if (m_pController->IsButtonHeld(PCB_Right))
	{
		m_PureInputDirection.x += 1;
		dir += rightDir;

	}

    if (m_pController->IsButtonPressed(PCB_Down))
    {
        if (m_pScene->GetOption("SoundOn"))
            m_pSoundPlayer->PlaySound(m_pScene->GetResourceManager()->GetAudioCue("Pickup")->GetSound());
    }
		

    dir.Normalize();
	m_PureInputDirection.Normalize();

    float speed = 10;

    m_pBody->applyCentralForce(btVector3(dir.x, dir.y, dir.z) * speed);

	btVector3 movementVelocity = m_pBody->getLinearVelocity();
	vec3 velocity = vec3(movementVelocity.x(), movementVelocity.y(), movementVelocity.z());

	if (velocity.Length() > 0.0f)
	{
		vec3 movementDirection = velocity.GetNormalized();
		m_MovementDirection = vec2(movementDirection.x, movementDirection.z);
	}

    m_InputDirection = vec2(dir.x, dir.z);
}
