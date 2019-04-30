#ifndef __SceneManager_H__
#define __SceneManager_H__

class Game;

class SceneManager
{
public:
    SceneManager(Game* pGame);
    ~SceneManager();

    void Update(float deltatime);
    void Draw();

    void OnEvent(Event* event);

	void LoadScene(std::string name, Scene* scene);
	void DeleteScene(std::string name);

    void PushScene(std::string name);
    void PopScene();
    void PopAllScenes();

	bool IsFrontScene(Scene* scene);
    int GetNumberOfLoadedScenes();


	Game* GetGame() { return m_pGame; }

private:
	Game* m_pGame;

    std::map<std::string, Scene*> m_Scenes;
    std::vector<Scene*> m_SceneStack;
};

#endif __SceneManager_H__