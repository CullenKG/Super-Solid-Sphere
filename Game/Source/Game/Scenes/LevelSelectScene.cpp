#include "GamePCH.h"

LevelSelectScene::LevelSelectScene(SceneManager* pSceneManager, ResourceManager* pResources) : Scene(pSceneManager, pResources)
{
	m_IsOpaque = false;
	m_UpdateNextScene = false;
}

LevelSelectScene::~LevelSelectScene()
{
}

void LevelSelectScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	Scene::OnSurfaceChanged(width, height);
}

void LevelSelectScene::LoadContent()
{
	Scene::LoadContent();

	m_pResources->AddMaterial("LevelSelectScene", new Material(m_pResources->GetShader("Texture"), m_FBO->GetColorTextureHandle()));

	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));

		// Buttons
		m_pGameObjects["Background"] = new GameObject(this, "Background", vec3(0, 0, -1), vec3(0, 0, 0), vec3(5, 5, 5), "Box", "MenuBackground");

		m_pGameObjects["LevelOne"] = new MenuButtonObject(this, "LevelOne", vec3(0.1f, 0.7f, -2), vec3(0, 0, 0), vec3(1.8f, 0.6f, 0.8f), "Box", "LevelOneButton");
		m_pGameObjects["LevelOne"]->SetRenderOrder(2);

        m_pGameObjects["LevelOneStar"] = new MenuButtonObject(this, "LevelOneStar", vec3(0.6f, 0.7f, -2), vec3(0, 0, 0), vec3(0.5, 0.5f, 0.5f), "Box", "Star");
        m_pGameObjects["LevelOneStar"]->SetRenderOrder(2);

        m_pGameObjects["LevelTwo"] = new MenuButtonObject(this, "LevelTwo", vec3(0.1f, -0.1f, -2), vec3(0, 0, 0), vec3(1.8f, 0.6f, 0.8f), "Box", "LevelTwoButton");
        m_pGameObjects["LevelTwo"]->SetRenderOrder(2);

        m_pGameObjects["LevelTwoStar"] = new MenuButtonObject(this, "LevelTwoStar", vec3(0.6f, -0.1f, -2), vec3(0, 0, 0), vec3(1.8f, 0.6f, 0.8f), "Box", "Star");
        m_pGameObjects["LevelTwoStar"]->SetRenderOrder(2);


		m_pGameObjects["BackButton"] = new MenuButtonObject(this, "BackButton", vec3(0, -1.5f, -2), vec3(0, 0, 0), vec3(1, 1, 1), "Box", "BackButton");
		m_pGameObjects["BackButton"]->SetRenderOrder(2);
	}
}

void LevelSelectScene::Update(float deltatime)
{
	m_MouseDepth = -2;

	Scene::Update(deltatime);

    m_pGameObjects["LevelOneStar"]->SetScale(m_CompletedLevels["LevelOne"] ? vec3(0.5f, 0.5f, 0.5f) : vec3(0));
    m_pGameObjects["LevelTwoStar"]->SetScale(m_CompletedLevels["LevelTwo"] ? vec3(0.5f, 0.5f, 0.5f) : vec3(0));


	if (m_pSceneManager->GetGame()->GetController(0)->IsButtonPressed(PCB_LeftMouse))
	{
		if (((MenuButtonObject*)m_pGameObjects["LevelOne"])->IsMouseOver(m_MouseWorldLocation))
		{
			m_pSceneManager->GetGame()->QueueEvent(new PopSceneEvent(true));
			m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("LevelOne"));
			m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("HUD"));

		}

        if (((MenuButtonObject*)m_pGameObjects["LevelTwo"])->IsMouseOver(m_MouseWorldLocation))
        {
            m_pSceneManager->GetGame()->QueueEvent(new PopSceneEvent(true));
            m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("LevelTwo"));
            m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("HUD"));

        }

		if (((MenuButtonObject*)m_pGameObjects["BackButton"])->IsMouseOver(m_MouseWorldLocation))
		{
			m_pSceneManager->GetGame()->QueueEvent(new PopSceneEvent(false));
		}
	}
}

void LevelSelectScene::Draw()
{
	glClear(GL_DEPTH_BUFFER_BIT);

	Scene::Draw();
}