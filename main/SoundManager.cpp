#include "Includes.hpp"

bool SoundManager::init_sound_engine()
{
    //
    // Create and initialize an instance of the default streaming manager. Note
    // that you can override the default streaming manager with your own. 
    //
    AkMemSettings memSettings{};
    AK::MemoryMgr::GetDefaultSettings(memSettings);
    if (AK::MemoryMgr::Init(&memSettings) != AK_Success)
    {
        assert(!"Could not create the memory manager.");
        return false;
    }

    //
    // Create and initialize an instance of the default streaming manager. Note
    // that you can override the default streaming manager with your own. 
    //

    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);

    // Customize the Stream Manager settings here.

    if (!AK::StreamMgr::Create(stmSettings))
    {
        assert(!"Could not create the Streaming Manager");
        return false;
    }

    AkDeviceSettings deviceSettings;
    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    // Customize the streaming device settings here.

    // CAkFilePackageLowLevelIODeferred::Init() creates a streaming device
    // in the Stream Manager, and registers itself as the File Location Resolver.
    if (g_lowLevelIO.Init(deviceSettings) != AK_Success)
    {
        assert(!"Could not create the streaming device and Low-Level I/O system");
        return false;
    }

    //
    // Create the Sound Engine
    // Using default initialization parameters
    //

    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);

    if (AK::SoundEngine::Init(&initSettings, &platformInitSettings) != AK_Success)
    {
        assert(!"Could not initialize the Sound Engine.");
        return false;
    }

    //
    // Initialize the music engine
    // Using default initialization parameters
    //

    AkMusicSettings musicInit;
    AK::MusicEngine::GetDefaultInitSettings(musicInit);

    if (AK::MusicEngine::Init(&musicInit) != AK_Success)
    {
        assert(!"Could not initialize the Music Engine.");
        return false;
    }

    //
    // Setup banks path
    //

    g_lowLevelIO.SetBasePath(AKTEXT("../Assets/SFX"));
    AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)"));

    //
    // Load banks synchronously (from file name).
    //

    AkBankID bankID; // Not used. These banks can be unloaded with their file name.
    AKRESULT eResult = AK::SoundEngine::LoadBank(L"Init.bnk", bankID);
    assert(eResult == AK_Success);

    // Register the main listener.
    AK::SoundEngine::RegisterGameObj(listener_id, "Listener");

    // Set one listener as the default.
    AK::SoundEngine::SetDefaultListeners(&listener_id, 1);

    // Register a game object for playing sounds
    AK::SoundEngine::RegisterGameObj(emitter_id, "Emitter");

    return true;
}

void SoundManager::terminate_sound_engine()
{
    AK::MusicEngine::Term();
    AK::SoundEngine::Term();
    g_lowLevelIO.Term();
    if (AK::IAkStreamMgr::Get())
        AK::IAkStreamMgr::Get()->Destroy();
    AK::MemoryMgr::Term();
}

SoundManager::SoundManager():
	listener_id(0),
	emitter_id(1)
{
	init_sound_engine();
}

bool SoundManager::load_soundbank(const wchar_t* name)
{
    AkBankID bankID; // Not used. These banks can be unloaded with their file name.
    AKRESULT eResult = AK::SoundEngine::LoadBank(name, bankID);
    return eResult == AK_Success;
}

bool SoundManager::unload_soundbank(const wchar_t* name)
{
    AKRESULT eResult = AK::SoundEngine::UnloadBank(name, NULL);
    return eResult == AK_Success;
}

AkPlayingID SoundManager::post_event(const wchar_t* event, AkUInt32 flags, AkCallbackFunc callback)
{
    return AK::SoundEngine::PostEvent(event, emitter_id, flags, callback);
}

SoundManager::~SoundManager()
{
	terminate_sound_engine();
}