#ifndef __LevelOneScene_H__
#define __LevelOneScene_H__

class LevelOneScene : public Scene
{
protected:
    bool m_TestingMode;

public:
	LevelOneScene(SceneManager* pSceneManager, ResourceManager* pResources);
	virtual ~LevelOneScene();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
	virtual void LoadContent();

	virtual void Update(float deltatime);
	virtual void Draw();
};

#endif // __LevelOneScene_H__
