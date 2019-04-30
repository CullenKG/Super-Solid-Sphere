#ifndef __LevelTwoScene_H__
#define __LevelTwoScene_H__

class LevelTwoScene : public Scene
{
protected:

public:
    LevelTwoScene(SceneManager* pSceneManager, ResourceManager* pResources);
    virtual ~LevelTwoScene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();
};

#endif // __LevelTwoScene_H__
