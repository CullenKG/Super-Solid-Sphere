#include "GamePCH.h"

LevelOneScene::LevelOneScene(SceneManager* pSceneManager, ResourceManager* pResources) : Scene(pSceneManager, pResources)
{
    m_UpdateNextScene = false;
    m_IsOpaque = true;
    m_TestingMode = false;
}

LevelOneScene::~LevelOneScene()
{
}

void LevelOneScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	Scene::OnSurfaceChanged(width, height);
}

void LevelOneScene::LoadContent()
{
	m_pBulletWorld = new BulletWorld(btVector3(0, -10, 0));

	// Create some game objects.
	{
		//Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 5.0f, 0), vec3(-15, 0, 0), vec3(1, 1, 1));

		m_pGameObjects["Skybox"] = new GameObject(this, "Skybox", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), "Skybox", "Skybox_Cubemap");
		m_pGameObjects["Skybox"]->SetRenderOrder(4);

		//m_pGameObjects["SkyboxSorta"] = new GameObject(this, "SkyboxSorta", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f), "Background", "Sky");

		// Point lights
		m_pLights["DirectionalLight"] = new DirectionalLight(this, "DirectionalLight", vec3(0, 1, 0), vec3(0.4f, -0.8f, 0.6f));
		m_pLights["DirectionalLight"]->SetLightColor(vec3(0.3f, 0.3f, 0.3f), vec3(0.6f, 0.6f, 0.6f), vec3(0.8f, 0.8f, 0.8f));

		m_pLights["PointLight1"] = new PointLight(this, "PointLight1", vec3(0, 3, 0), 1.0f, 0.09f, 0.032f);
		m_pLights["PointLight1"]->SetLightColor(vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

		//m_pLights["PointLight2"] = new PointLight(this, "PointLight2", vec3(0, 2, 5), 1.0f, 0.09f, 0.032f);
		//m_pLights["PointLight2"]->SetLightColor(vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

		// Player
		m_pGameObjects["Player"] = new PlayerObject(this, "Player", vec3(0, 0.5, 0), vec3(0, 0, 0), vec3(1.0, 1.0f, 1.0f), "Sphere", "Crystal");
		m_pGameObjects["Player"]->CreateSphereBody(1.0f, 0.5f, btCollisionObject::CollisionFlags::CF_CHARACTER_OBJECT);
		((PlayerObject*)m_pGameObjects["Player"])->SetController(m_pSceneManager->GetGame()->GetController(0));
		((CameraObject*)m_pGameObjects["Camera"])->SetObjectToFollow(m_pGameObjects["Player"]);

		// Ground
		m_pGameObjects["Ground"] = new GameObject(this, "Ground", vec3(0, -2.5, 0), vec3(0, 0, 0), vec3(10, 5, 10), "Cube", "Brick");
		m_pGameObjects["Ground"]->CreateBoxBody(0.0f);

        m_pGameObjects["Ground2"] = new GameObject(this, "Ground2", vec3(0, -2.5, 15), vec3(0, 0, 0), vec3(2, 5, 20), "Cube", "Brick");
        m_pGameObjects["Ground2"]->CreateBoxBody(0.0f);

        m_pGameObjects["Ground3"] = new GameObject(this, "Ground3", vec3(10, -5, 22.5), vec3(0, 0, 0), vec3(20, 5, 5), "Cube", "Brick");
        m_pGameObjects["Ground3"]->CreateBoxBody(0.0f);

        m_pGameObjects["Ground4"] = new GameObject(this, "Ground4", vec3(25, -10, 22.5), vec3(0, 0, 0), vec3(10, 5, 10), "Cube", "Brick");
        m_pGameObjects["Ground4"]->CreateBoxBody(0.0f);

        m_pGameObjects["EndPoint"] = new EndPointObject(this, "EndPoint", vec3(25, -7.5, 22.5), vec3(0, 0, 0), vec3(1, 1, 1), "Sphere", "Crystal");
        m_pGameObjects["EndPoint"]->CreateBoxBody(0.0f, btCollisionObject::CollisionFlags::CF_NO_CONTACT_RESPONSE);
	}
}

void LevelOneScene::Update(float deltatime)
{
	Scene::Update(deltatime);

    if (m_TestingMode == true)
    {
        if (m_pSceneManager->GetGame()->GetController(0)->IsButtonHeld(PCB_Up))
        {
            m_pGameObjects["Camera"]->SetPosition(m_pGameObjects["Camera"]->GetPosition() + ((CameraObject*)m_pGameObjects["Camera"])->GetForwardDirection() * 10 * deltatime);
        }
        if (m_pSceneManager->GetGame()->GetController(0)->IsButtonHeld(PCB_Down))
        {
            m_pGameObjects["Camera"]->SetPosition(m_pGameObjects["Camera"]->GetPosition() - ((CameraObject*)m_pGameObjects["Camera"])->GetForwardDirection() * 10 * deltatime);
        }

        if (m_pSceneManager->GetGame()->GetController(0)->IsButtonHeld(PCB_Left))
        {
            m_pGameObjects["Camera"]->SetRotation(m_pGameObjects["Camera"]->GetRotation() + vec3(0, -45, 0) * deltatime);
        }
        if (m_pSceneManager->GetGame()->GetController(0)->IsButtonHeld(PCB_Right))
        {
            m_pGameObjects["Camera"]->SetRotation(m_pGameObjects["Camera"]->GetRotation() + vec3(0, 45, 0) * deltatime);
        }
    }

    m_pLights["PointLight1"]->SetPosition(m_pGameObjects["Player"]->GetPosition() + vec3(0, 2, 0));

    if (((PlayerObject*)m_pGameObjects["Player"])->HasBeatLevel() == true)
    {
        SetCompletedLevel("LevelOne", true);
        m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("GameOver"));
    }

	if (m_pGameObjects["Player"]->GetPosition().y < -10)
	{
		m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("GameOver"));
	}

	if (m_pSceneManager->GetGame()->GetController(0)->IsButtonPressed(PCB_R))
	{
		m_pGameObjects["Player"]->Reset();
		m_pGameObjects["Camera"]->Reset();
	}

    if (m_pSceneManager->GetGame()->GetController(0)->IsButtonPressed(PCB_Q))
    {
        if (m_TestingMode == false)
        {
            ((PlayerObject*)m_pGameObjects["Player"])->SetController(nullptr);
            ((CameraObject*)m_pGameObjects["Camera"])->SetObjectToFollow(nullptr);

            m_TestingMode = true;
        }
        else
        {
            ((PlayerObject*)m_pGameObjects["Player"])->SetController(m_pSceneManager->GetGame()->GetController(0));
            ((CameraObject*)m_pGameObjects["Camera"])->SetObjectToFollow(m_pGameObjects["Player"]);
            m_TestingMode = false;
        }
        
    }

	if (m_pSceneManager->GetGame()->GetController(0)->IsButtonPressed(PCB_P))
	{
		m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("Pause"));
	}
}

void LevelOneScene::Draw()
{
	Scene::Draw();
}
