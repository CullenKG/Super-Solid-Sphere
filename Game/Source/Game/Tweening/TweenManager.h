#ifndef __TweenManager_H__
#define __TweenManager_H__

class Game;

class TweenManager
{
protected:
    Game* m_pGame;

public:
	TweenManager(Game* game);
	~TweenManager();

	void Update(float deltatime);

	TweenObject* StartTween(TweenObject::TweenFunction tweenFunction, float startPosition, float endPosition, double timeToMove);

	void DeactivateTween(TweenObject* tween);

private:
	std::vector<TweenObject*> m_ActiveTweens;
	std::vector<TweenObject*> m_InactiveTweens;
};

#endif //__TweenManager_H__