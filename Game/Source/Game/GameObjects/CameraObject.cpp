#include "GamePCH.h"

CameraObject::CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: GameObject( pScene, name, pos, rot, scale, 0, 0 )
{
    m_ObjectToFollow = 0;
	m_CurrentRotation = rot;

	m_MovingToX = rot.x;
	m_MovingToY = rot.y;
	m_MovingToZ = rot.z;

	m_CameraXTween = nullptr;
	m_CameraYTween = nullptr;
	m_CameraZTween = nullptr;
}

CameraObject::~CameraObject()
{
}

void CameraObject::Update(float deltatime)
{
	if (m_CameraXTween != nullptr)
	{
		if (m_CameraXTween->IsFinished())
		{
			m_CameraXTween = nullptr;
		}	
		else
		{
			m_CurrentRotation.x = m_CameraXTween->GetCurrentPosition();
		}
	}

	if (m_CameraYTween != nullptr)
	{
		if (m_CameraYTween->IsFinished())
		{
			m_CameraYTween = nullptr;
		}			
		else
		{
			m_CurrentRotation.y = m_CameraYTween->GetCurrentPosition();
		}
	}

	if (m_CameraZTween != nullptr)
	{
		if (m_CameraZTween->IsFinished())
		{
			m_CameraZTween = nullptr;
		}
		else
		{
			m_CurrentRotation.z = m_CameraZTween->GetCurrentPosition();
		}	
	}

    if (m_ObjectToFollow)
    {
		float angleX = 0.0f;
		float angleY = 0.0f;
		float angleZ = 0.0f;

        vec2 inputDirection = ((PlayerObject*)m_ObjectToFollow)->GetPureInput();
		vec2 movementDirection = ((PlayerObject*)m_ObjectToFollow)->GetMovementDirection();

		angleX = inputDirection.y * 10;
		angleY = atan2f(movementDirection.x, movementDirection.y) * 180 / PI * -1;
		angleZ = inputDirection.x * 10;

		

		if (m_Rotation.x + angleX != m_MovingToX) 			
		{
			if (m_CameraXTween != nullptr)
				m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->DeactivateTween(m_CameraXTween);

			m_MovingToX = m_Rotation.x + angleX;
			m_CameraXTween = m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->StartTween(TweenFunc_Linear, m_CurrentRotation.x, m_MovingToX - m_CurrentRotation.x, 0.5);
		}

		if (m_Rotation.y + angleY != m_MovingToY)
		{
			if (m_CameraYTween != nullptr)
				m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->DeactivateTween(m_CameraYTween);

			m_MovingToY = m_Rotation.y + angleY;
			m_CameraYTween = m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->StartTween(TweenFunc_Linear, m_CurrentRotation.y, m_MovingToY - m_CurrentRotation.y, 1.0);
		}

		if (m_Rotation.z - angleZ != m_MovingToZ)
		{
			if (m_CameraZTween != nullptr)
				m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->DeactivateTween(m_CameraZTween);

			m_MovingToZ = m_Rotation.z - angleZ;
			m_CameraZTween = m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->StartTween(TweenFunc_Linear, m_CurrentRotation.z, m_MovingToZ - m_CurrentRotation.z, 0.5);
		}

		if (m_CurrentRotation.z + angleX > 360.0f)
			m_CurrentRotation.z -= 180.0f;
    }

    m_MatView.SetIdentity();
    m_MatViewSkyBox.SetIdentity();

    if (m_ObjectToFollow)
    {
		float dist = 10;
		m_MatView.Translate(0, 0, -dist);
		m_MatView.Rotate(m_CurrentRotation.z, 0, 0, 1);
		m_MatView.Rotate(m_CurrentRotation.x, 1, 0, 0);
		m_MatView.Rotate(m_CurrentRotation.y, 0, 1, 0);

        m_MatView.Translate(m_ObjectToFollow->GetPosition());

        m_MatViewSkyBox.Translate(0, 0, -dist);
        m_MatViewSkyBox.Rotate(m_Rotation.x, 1, 0, 0);
        m_MatViewSkyBox.Rotate(m_CurrentRotation.y, 0, 1, 0);
        m_MatViewSkyBox.Rotate(m_Rotation.z, 0, 0, 1);
        m_MatViewSkyBox.Translate(m_ObjectToFollow->GetPosition());
    }
	else
	{
		m_MatView.Rotate(m_Rotation.z, 0, 0, 1);
		m_MatView.Rotate(m_Rotation.x, 1, 0, 0);
		m_MatView.Rotate(m_Rotation.y, 0, 1, 0);
		m_MatView.Translate(m_Position);
	}
    
	m_ForwardDirection = m_MatViewSkyBox.GetAt();
	m_RightDirection = m_MatViewSkyBox.GetRight();

    m_MatView.Inverse();
    m_MatViewSkyBox.Inverse();

	

    m_MatProj.CreatePerspectiveVFoV(45, 600.0f / 600.0f, 0.01f, 1000);

    GameObject::Update(deltatime);
}

void CameraObject::Reset()
{
	GameObject::Reset();

	m_CurrentRotation = m_InitialRotation;

	m_MovingToX = m_InitialRotation.x;
	m_MovingToY = m_InitialRotation.y;
	m_MovingToZ = m_InitialRotation.z;

	m_CameraXTween = nullptr;
	m_CameraYTween = nullptr;
	m_CameraZTween = nullptr;
}

void CameraObject::SetObjectToFollow(GameObject* object)
{
    m_ObjectToFollow = object;
}
