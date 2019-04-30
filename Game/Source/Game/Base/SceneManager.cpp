#include "GamePCH.h"

SceneManager::SceneManager(Game * pGame)
{
    m_pGame = pGame;
}

SceneManager::~SceneManager()
{
    for (auto object : m_Scenes)
        delete object.second;
}

void SceneManager::Update(float deltatime)
{
    for (unsigned int i = 0; i < m_SceneStack.size(); i++)
	{
		bool updateScene = true;

		for (unsigned int j = i; j < m_SceneStack.size(); j++)
		{
			if (j == i)
				continue;

			if (m_SceneStack[j]->SendsUpdateToNextScene() == false)
			{
				updateScene = false;
				break;
			}
		}

		if (updateScene)
		{
			m_SceneStack[i]->Update(deltatime);
		}       
    }
}

void SceneManager::Draw()
{
    for (unsigned int i = 0; i < m_SceneStack.size(); i++)
    {
		bool drawScene = true;

		for (unsigned int j = i; j < m_SceneStack.size(); j++)
		{
			if (j == i)
				continue;

			if (m_SceneStack[j]->IsOpaque() == true)
			{
				drawScene = false;
				break;
			}
		}

		if (drawScene)
		{
			m_SceneStack[i]->Draw();
		}	
    }
}

void SceneManager::LoadScene(std::string name, Scene* scene)
{
    m_Scenes[name] = scene;
    m_Scenes[name]->LoadContent();
}

void SceneManager::DeleteScene(std::string name)
{
    Scene* scene = m_Scenes[name];

    delete scene;
    m_Scenes.erase(name);
}

void SceneManager::OnEvent(Event* event)
{
    if (event->GetEventType() == EventType_PushScene)
    {
        PushSceneEvent* pushEvent = (PushSceneEvent*)event;

        PushScene(pushEvent->GetSceneName());
    }
    else if (event->GetEventType() == EventType_PopScene)
    {
        PopSceneEvent* popEvent = (PopSceneEvent*)event;

        if (popEvent->ShouldPopAllScenes())
        {
            PopAllScenes();
        }
        else
        {
            PopScene();
        }
    }
    else
    {
		for (unsigned int i = 0; i < m_SceneStack.size(); i++)
		{
			bool updateScene = true;

			for (unsigned int j = i; j < m_SceneStack.size(); j++)
			{
				if (j == i)
					continue;

				if (m_SceneStack[j]->SendsUpdateToNextScene() == false)
				{
					updateScene = false;
					break;
				}
			}

			if (updateScene)
			{
				m_SceneStack[i]->OnEvent(event);
			}
		}
    }
}

void SceneManager::PushScene(std::string name)
{
    m_SceneStack.push_back(m_Scenes[name]);
}

void SceneManager::PopScene()
{
    m_SceneStack.pop_back();
}

void SceneManager::PopAllScenes()
{
    while (m_SceneStack.size() > 0)
    {
        m_SceneStack.pop_back();
    }
}

bool SceneManager::IsFrontScene(Scene* scene)
{
	auto pos = std::find(m_SceneStack.begin(), m_SceneStack.end(), scene);

	if (pos == m_SceneStack.end() - 1)
		return true;

	return false;
}

int SceneManager::GetNumberOfLoadedScenes()
{
    return m_Scenes.size();
}
