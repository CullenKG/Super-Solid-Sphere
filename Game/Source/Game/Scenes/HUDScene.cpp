#include "GamePCH.h"

HUDScene::HUDScene(SceneManager* pSceneManager, ResourceManager* pResources) : Scene(pSceneManager, pResources)
{
	m_IsOpaque = false;
	m_UpdateNextScene = true;
}

HUDScene::~HUDScene()
{
}

void HUDScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	Scene::OnSurfaceChanged(width, height);
}

void HUDScene::LoadContent()
{
	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));

	}
}

void HUDScene::Update(float deltatime)
{
	Scene::Update(deltatime);
}

void HUDScene::Draw()
{

	//glClear(GL_DEPTH_BUFFER_BIT);

	Scene::Draw();
}