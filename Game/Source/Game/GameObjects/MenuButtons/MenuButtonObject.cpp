#include "GamePCH.h"

MenuButtonObject::MenuButtonObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh * pMesh, Material * pMaterial)
	: GameObject(pScene, name, pos, rot, scale, pMesh, pMaterial)
{
	m_InitialScale = scale;
	m_Tween = nullptr;
	m_CurrentTweenScale = 1.0f;

	m_pSoundPlayer = new SoundPlayer();
}

MenuButtonObject::MenuButtonObject(Scene * pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname)
	: GameObject(pScene, name, pos, rot, scale, meshname, materialname)
{
	m_InitialScale = scale;
	m_Tween = nullptr;
	m_CurrentTweenScale = 1.0f;

	m_pSoundPlayer = new SoundPlayer();
}

MenuButtonObject::~MenuButtonObject()
{
	delete m_pSoundPlayer;
}

void MenuButtonObject::Update(float deltatime)
{
	// Check if we are currently tweening
	if (m_Tween != nullptr)
	{
		// If the current tween is finished set tween to be null
		if (m_Tween->IsFinished())
			m_Tween = nullptr;
		else
		{
			// If we are tweening get the current scale from the tween object
			m_CurrentTweenScale = m_Tween->GetCurrentPosition();

			// Apply tween scale to object
			m_Scale.x = m_InitialScale.x * m_CurrentTweenScale;
			m_Scale.y = m_InitialScale.y * m_CurrentTweenScale;
		}
	}

	// Check if mouse is over this object
	if (IsMouseOver(m_pScene->GetMouseWorldLocation()))
	{
		// If mouse wasn't over this object last frame
		if (m_IsMouseOver == false)
		{
			// Play select sound
            if (m_pScene->GetOption("SoundOn"))
			    m_pSoundPlayer->PlaySound(m_pScene->GetResourceManager()->GetAudioCue("MenuSelect")->GetSound());

			// If an old tween object was running deactivate it
			if (m_Tween != nullptr)
				m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->DeactivateTween(m_Tween);

			// Get a new tween object
			m_Tween = m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->StartTween(&TweenFunc_ElasticEaseOut, m_CurrentTweenScale, 1.5f - m_CurrentTweenScale, 0.5f);
		}

		// Set mouseover to be true
		m_IsMouseOver = true;
	}
	else
	{
		// If mouse was over last frame
		if (m_IsMouseOver == true)
		{
			// Get a new tween object
			m_Tween = m_pScene->GetSceneManager()->GetGame()->GetTweenManager()->StartTween(&TweenFunc_SineEaseIn, m_CurrentTweenScale, -(m_CurrentTweenScale - 1.0f), 0.2f);
		}

		// Set mouseover to be false
		m_IsMouseOver = false;
	}
}

bool MenuButtonObject::IsMouseOver(vec2 mousePosition)
{
	vec3 halfScale = m_InitialScale / 2;

	float left = m_Position.x - halfScale.x;
	float right = m_Position.x + halfScale.x;
	float top = m_Position.y + halfScale.y;
	float bottom = m_Position.y - halfScale.y;

	if (mousePosition.x > left && mousePosition.x < right && mousePosition.y > bottom && mousePosition.y < top) 
	{
		return true;
	}	

	return false;
}
