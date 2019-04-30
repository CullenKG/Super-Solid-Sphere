#ifndef __ResetEvent_H__
#define __ResetEvent_H__

class MyResetEvent : public Event
{
public:
	MyResetEvent()
	{
		m_EventType = EventType_Reset;
	}
};

#endif //__ResetEvent_H__