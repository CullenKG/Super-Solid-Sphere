#include "GamePCH.h"

PlayerController::PlayerController()
{
    Clear();
}

PlayerController::~PlayerController()
{
}

void PlayerController::Clear()
{
    m_ButtonFlags = 0;
    m_LastButtonFlags = 0;
}

void PlayerController::Update(float deltatime)
{
    m_LastButtonFlags = m_ButtonFlags;
}

void PlayerController::SetButtonPressed(PlayerControllerButtons button)
{
    m_ButtonFlags |= button;
}

void PlayerController::SetButtonReleased(PlayerControllerButtons button)
{
    m_ButtonFlags &= ~button;
}

bool PlayerController::IsButtonPressed(PlayerControllerButtons button)
{
    if( (m_ButtonFlags & button) && (m_LastButtonFlags & button) == 0)
        return true;

    return false;
}

bool PlayerController::IsButtonHeld(PlayerControllerButtons button)
{
    if (m_ButtonFlags & button)
        return true;

    return false;
}

void PlayerController::OnEvent(Event* pEvent)
{
    if( pEvent->GetEventType() == EventType_Input )
    {
        InputEvent* pInputEvent = (InputEvent*)pEvent;

        if( pInputEvent->GetInputDeviceType() == InputDeviceType_Keyboard )
        {
            if( pInputEvent->GetInputState() == InputState_Pressed )
            {
                if( pInputEvent->GetID() == VK_UP || pInputEvent->GetID() == 'W' )
                    SetButtonPressed( PCB_Up );
                if( pInputEvent->GetID() == VK_DOWN || pInputEvent->GetID() == 'S' )
                    SetButtonPressed( PCB_Down );
                if( pInputEvent->GetID() == VK_LEFT || pInputEvent->GetID() == 'A' )
                    SetButtonPressed( PCB_Left );
                if( pInputEvent->GetID() == VK_RIGHT || pInputEvent->GetID() == 'D' )
                    SetButtonPressed( PCB_Right );
				if (pInputEvent->GetID() == 'R')
					SetButtonPressed(PCB_R);
				if (pInputEvent->GetID() == 'Q')
					SetButtonPressed(PCB_Q);
				if (pInputEvent->GetID() == 'E')
					SetButtonPressed(PCB_E);
				if (pInputEvent->GetID() == 'P')
					SetButtonPressed(PCB_P);
            }

            if( pInputEvent->GetInputState() == InputState_Released )
            {
                if( pInputEvent->GetID() == VK_UP || pInputEvent->GetID() == 'W' )
                    SetButtonReleased( PCB_Up );
                if( pInputEvent->GetID() == VK_DOWN || pInputEvent->GetID() == 'S' )
                    SetButtonReleased( PCB_Down );
                if( pInputEvent->GetID() == VK_LEFT || pInputEvent->GetID() == 'A' )
                    SetButtonReleased( PCB_Left );
                if( pInputEvent->GetID() == VK_RIGHT || pInputEvent->GetID() == 'D' )
                    SetButtonReleased( PCB_Right );
				if (pInputEvent->GetID() == 'R')
					SetButtonReleased(PCB_R);
				if (pInputEvent->GetID() == 'Q')
					SetButtonReleased(PCB_Q);
				if (pInputEvent->GetID() == 'E')
					SetButtonReleased(PCB_E);
				if (pInputEvent->GetID() == 'P')
					SetButtonReleased(PCB_P);
            }
        }

        if (pInputEvent->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            if (pInputEvent->GetInputState() == InputState_Moved)
            {
                m_MouseLocation = pInputEvent->GetPosition();
            }

            if (pInputEvent->GetInputState() == InputState_Pressed)
            {
                if (pInputEvent->GetID() == 0)
                    SetButtonPressed(PCB_LeftMouse);
            }
            
            if (pInputEvent->GetInputState() == InputState_Released)
            {
                if (pInputEvent->GetID() == 0)
                    SetButtonReleased(PCB_LeftMouse);
            }
        }

        if( pInputEvent->GetInputDeviceType() == InputDeviceType_Gamepad )
        {
            if( pInputEvent->GetInputState() == InputState_Held )
            {
                if( pInputEvent->GetGamepadID() == GamepadID_LeftStick )
                {
                    if( pInputEvent->GetPosition().y > 0 )
                        SetButtonReleased( PCB_Up );
                    if( pInputEvent->GetPosition().y < 0 )
                        SetButtonReleased( PCB_Down );
                    if( pInputEvent->GetPosition().x < 0 )
                        SetButtonReleased( PCB_Left );
                    if( pInputEvent->GetPosition().x > 0 )
                        SetButtonReleased( PCB_Right );

                    if( pInputEvent->GetPosition().y == 0 )
                    {
                        SetButtonReleased( PCB_Up );
                        SetButtonReleased( PCB_Down );
                    }
                    if( pInputEvent->GetPosition().x == 0 )
                    {
                        SetButtonReleased( PCB_Left );
                        SetButtonReleased( PCB_Right );
                    }
                }
            }
        }
    }
}