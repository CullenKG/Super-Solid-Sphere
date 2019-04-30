#ifndef __GamePCH_H__
#define __GamePCH_H__

#include "../../Libraries/Framework/Source/FrameworkPCH.h"
#pragma warning( push )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4263 )
#pragma warning( disable : 4264 )
#pragma warning( disable : 4640 )
#pragma warning( disable : 4305 )
#include "../../Libraries/bullet3/src/btBulletDynamicsCommon.h"
#pragma warning( pop )

#include <queue>
#include <xaudio2.h>

#include "Game/Base/FBODefinition.h"

#include "Physics/ContactListener.h"
#include "Physics/BulletWorld.h"
#include "Common/Audio/SoundPlayerXAudio.h"
#include "Common/Audio/WaveLoader.h"
#include "Common/Audio/AudioCue.h"

#include "Common/Memory/CPPList.h"
#include "Common/Memory/Memory.h"
#include "Common/Main/ImGuiManager.h"

#include "Game/Tweening/TweenFuncs.h"
#include "Game/Tweening/TweenObject.h"
#include "Game/Tweening/TweenManager.h"

#include "Game/Mesh/VertexFormat.h"
#include "Game/Mesh/Material.h"
#include "Game/Mesh/Mesh.h"

#include "Game/GameObjects/PlayerController.h"
#include "Game/GameObjects/GameObject.h"
#include "Game/GameObjects/CameraObject.h"
#include "Game/GameObjects/PlayerObject.h"
#include "Game/GameObjects/MenuButtons/MenuButtonObject.h"
#include "Game/GameObjects/SoupPickupObject.h"
#include "Game/GameObjects/Lights/LightObject.h"
#include "Game/GameObjects/Lights/DirectionalLight.h"
#include "Game/GameObjects/Lights/PointLight.h"
#include "Game/GameObjects/EndPointObject.h"


#include "Game/Base/ResourceManager.h"
#include "Game/Base/Scene.h"
#include "Game/Base/SceneManager.h"

#include "Game/SampleScene.h"
#include "Game/Scenes/LoadingScene.h"
#include "Game/Scenes/MainMenuScene.h"
#include "Game/Scenes/OptionsScene.h"
#include "Game/Scenes/LevelOneScene.h"
#include "Game/Scenes/LevelTwoScene.h"
#include "Game/Scenes/PauseScene.h"
#include "Game/Scenes/LevelSelectScene.h"
#include "Game/Scenes/GameOverScene.h"
#include "Game/Scenes/HUDScene.h"

#include "Game/Base/Game.h"

#endif //__GamePCH_H__
