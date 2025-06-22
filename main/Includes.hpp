#pragma once
// SFML modules to work with graphics
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

// nlohmann json for 
// serializing and deserializing objects
#include "json.hpp"

// entt framework for ECS implementation
#include "entt.hpp"

// Audiokinetic Wwise sdk for audio
#include "AK/MusicEngine/Common/AkMusicEngine.h"
#include "AK/SoundEngine/Common/AkMemoryMgr.h"
#include "AK/SoundEngine/Common/AkMemoryMgrModule.h"

#include <AK/SoundEngine/Common/IAkStreamMgr.h>                 // Streaming Manager
#include <AK/Tools/Common/AkPlatformFuncs.h>                    // Thread defines
#include <AkFilePackageLowLevelIODeferred.h>					// Sample low-level I/O implementation

#include <AK/SoundEngine/Common/AkSoundEngine.h>

// TGUI includes for GUI via sfml
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

// stdlib modules
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <string_view>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <iostream>


#include "JSONUtilities.hpp"

// components




// systems
#include "BaseSystem.hpp"

#include "BaseScene.hpp"

// manager classes
#include "SystemManager.hpp"
#include "InputManager.hpp"
#include "SceneManager.hpp"
#include "SoundManager.hpp"
#include "ResourceManager.hpp"

// core engine classes
#include "Settings.hpp"
#include "Game.hpp"

#include "Tetramino.hpp"
#include "Field.hpp"

#include "GUI.hpp"

// scene classes
#include "scene_MainMenu.hpp"
#include "scene_Gameplay.hpp"

const std::string AssetPath = "..\\assets";

// scene names
inline auto const menu_scene = "menu";
inline auto const gameplay_scene = "gameplay";


