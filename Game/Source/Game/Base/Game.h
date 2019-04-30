#ifndef __Game_H__
#define __Game_H__

class ShaderProgram;

class Game : public GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;

    unsigned int m_WindowWidth;
    unsigned int m_WindowHeight;

    std::queue<Event*> m_EventQueue;

    ResourceManager* m_pResources;

    SceneManager* m_pSceneManager;
	TweenManager* m_pTweenManager;

    PlayerController m_Controllers[4];

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void QueueEvent(Event* pEvent);
    virtual void ProcessEvents();
    virtual void OnEvent(Event* pEvent);

    virtual void Update(float deltatime);
    virtual void Draw();

    unsigned int GetWindowWidth() { return m_WindowWidth; }
    unsigned int GetWindowHeight() { return m_WindowHeight; }

    PlayerController* GetController(int index) { return &m_Controllers[index]; }
	TweenManager* GetTweenManager() { return m_pTweenManager; }
};

#endif //__Game_H__
