#ifndef __MainMenuScene_H__
#define __MainMenuScene_H__

class MainMenuScene : public Scene
{
protected:
	TweenObject* m_Tween;

public:
    MainMenuScene(SceneManager* pSceneManager, ResourceManager* pResources);
    virtual ~MainMenuScene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();
};

#endif // __MainMenuScene_H__
