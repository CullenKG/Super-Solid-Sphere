#include "GamePCH.h"

TweenManager::TweenManager(Game* game)
{
    m_pGame = game;

	for (int i = 0; i < 20; i++)
	{
		m_InactiveTweens.push_back(new TweenObject());
	}
}

TweenManager::~TweenManager()
{
	for (auto tween : m_ActiveTweens)
		delete tween;

	for (auto tween : m_InactiveTweens)
		delete tween;
}

void TweenManager::Update(float deltatime)
{
	for (unsigned int i = 0; i < m_ActiveTweens.size(); i++)
	{
		m_ActiveTweens[i]->Update(deltatime);

		if (m_ActiveTweens[i]->IsFinished())
		{
			DeactivateTween(m_ActiveTweens[i]);
		}
	}
}

TweenObject* TweenManager::StartTween(TweenObject::TweenFunction tweenFunction, float startPosition, float endPosition, double timeToMove)
{
	TweenObject* tween = m_InactiveTweens.front();
	tween->Init(tweenFunction, startPosition, endPosition, timeToMove);

	m_ActiveTweens.push_back(tween);

	m_InactiveTweens.erase(m_InactiveTweens.begin());

	return tween;
}

void TweenManager::DeactivateTween(TweenObject * tween)
{
	auto pos = std::find(m_ActiveTweens.begin(), m_ActiveTweens.end(), tween);

	if (pos == m_ActiveTweens.end())
		return;

	auto index = std::distance(m_ActiveTweens.begin(), pos);

	m_ActiveTweens[index]->Reset();
	m_InactiveTweens.push_back(m_ActiveTweens[index]);
	m_ActiveTweens.erase(pos);
}