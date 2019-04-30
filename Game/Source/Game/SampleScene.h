#ifndef __SampleScene_H__
#define __SampleScene_H__

class Game;

class SampleScene : public Scene
{
protected:

public:
    SampleScene(SceneManager* pSceneManager, ResourceManager* pResources);
    virtual ~SampleScene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void Update(float deltatime);
    virtual void Draw();
};

#endif //__Scene_H__
