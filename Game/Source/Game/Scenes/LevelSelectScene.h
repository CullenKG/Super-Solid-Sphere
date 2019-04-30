#ifndef __LevelSelectScene_H__
#define __LevelSelectScene_H__

class LevelSelectScene : public Scene
{
public:
	LevelSelectScene(SceneManager* pSceneManager, ResourceManager* pResources);
	virtual ~LevelSelectScene();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
	virtual void LoadContent();

	virtual void Update(float deltatime);
	virtual void Draw();
};

#endif // __LevelSelectScene_H__
