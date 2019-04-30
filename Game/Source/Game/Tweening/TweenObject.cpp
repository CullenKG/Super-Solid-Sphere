#include "GamePCH.h"

TweenObject::TweenObject() :
	m_pTweenFunction(nullptr),
	m_StartPosition(0.0f),
	m_EndPosition(0.0f),
	m_CurrentPosition(0.0f),
	m_TimeToMove(0.0),
	m_TimeElapsed(-1.0),
	m_IsFinished(false)
{
}

TweenObject::~TweenObject()
{
}

void TweenObject::Init(TweenFunction tweenFunction, float startPosition, float endPosition, double timeToMove)
{
	m_pTweenFunction = tweenFunction;
	m_StartPosition = startPosition;
	m_CurrentPosition = startPosition;
	m_EndPosition = endPosition;
	m_TimeToMove = timeToMove;
	m_TimeElapsed = 0.0;
	m_IsFinished = false;
}

void TweenObject::Reset()
{
	m_pTweenFunction = nullptr;
	m_StartPosition = 0.0f;
	m_EndPosition = 0.0f;
	m_CurrentPosition = 0.0f;
	m_TimeToMove = 0.0;
	m_TimeElapsed = -1.0;
}

void TweenObject::Update(float deltatime)
{
	if (m_TimeElapsed == -1.0)
		return;

	if (m_TimeElapsed < m_TimeToMove)
	{
		m_TimeElapsed += deltatime;

		if (m_TimeElapsed > m_TimeToMove)
		{
			m_TimeElapsed = m_TimeToMove;
		}
	}

	m_CurrentPosition = m_pTweenFunction(m_StartPosition, m_EndPosition, m_TimeElapsed, m_TimeToMove);

	if (m_CurrentPosition == m_StartPosition + m_EndPosition)
		m_IsFinished = true;
}
