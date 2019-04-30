#include "GamePCH.h"

PauseScene::PauseScene(SceneManager* pSceneManager, ResourceManager* pResources) : Scene(pSceneManager, pResources)
{
	m_IsOpaque = false;
	m_UpdateNextScene = false;
}

PauseScene::~PauseScene()
{
}

void PauseScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	Scene::OnSurfaceChanged(width, height);
}

void PauseScene::LoadContent()
{
	Scene::LoadContent();

	m_pResources->AddMaterial("PauseScene", new Material(m_pResources->GetShader("Texture"), m_FBO->GetColorTextureHandle()));


	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));

		// Buttons
		m_pGameObjects["Background"] = new GameObject(this, "Background", vec3(0, 0, -1), vec3(0, 0, 0), vec3(5, 5, 5), "Box", "MenuBackground");

		m_pGameObjects["BackButton"] = new MenuButtonObject(this, "BackButton", vec3(0, -1.5f, -2), vec3(0, 0, 0), vec3(2, 1, 1), "Box", "BackButton");
		m_pGameObjects["BackButton"]->SetRenderOrder(2);
	}
}

void PauseScene::Update(float deltatime)
{
	m_MouseDepth = -2;

	Scene::Update(deltatime);

	if (m_pSceneManager->GetGame()->GetController(0)->IsButtonPressed(PCB_LeftMouse))
	{
		if (((MenuButtonObject*)m_pGameObjects["BackButton"])->IsMouseOver(m_MouseWorldLocation))
		{
			m_pSceneManager->GetGame()->QueueEvent(new PopSceneEvent(false));
		}
	}
}

void PauseScene::Draw()
{
	glClear(GL_DEPTH_BUFFER_BIT);

	Scene::Draw();
}