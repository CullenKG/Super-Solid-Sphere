#ifndef __TweenObject_H__
#define __TweenObject_H__

class TweenObject
{
public:
	typedef float(*TweenFunction)(float startvalue, float valuerange, double timepassed, double totaltime);

	TweenObject();
	~TweenObject();

	void Init(TweenFunction tweenFunction, float startPosition, float endPosition, double timeToMove);
	void Reset();

	void Update(float deltatime);

	float GetCurrentPosition() { return m_CurrentPosition; }

	bool IsFinished() { return m_IsFinished; }

private:
	TweenFunction m_pTweenFunction;

	float m_StartPosition;
	float m_EndPosition;
	float m_CurrentPosition;

	double m_TimeToMove;
	double m_TimeElapsed;

	bool m_IsFinished;
};

#endif //__TweenObject_H__
