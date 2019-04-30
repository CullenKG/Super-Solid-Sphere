#ifndef __GameOverScene_H__
#define __GameOverScene_H__

class GameOverScene : public Scene
{
public:
	GameOverScene(SceneManager* pSceneManager, ResourceManager* pResources);
	virtual ~GameOverScene();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
	virtual void LoadContent();

	virtual void Update(float deltatime);
	virtual void Draw();
};

#endif // __GameOverScene_H__
