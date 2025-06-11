#pragma once

class SoundManager
{
private:
	CAkFilePackageLowLevelIODeferred g_lowLevelIO;

	bool init_sound_engine();
	void terminate_sound_engine();
public:
	const AkGameObjectID emitter_id;
	const AkGameObjectID listener_id;

	SoundManager();

	bool load_soundbank(const wchar_t* name);
	bool unload_soundbank(const wchar_t* name);

	AkPlayingID post_event(const wchar_t* event, AkUInt32 flags = 0, AkCallbackFunc callback = NULL);
	
	~SoundManager();
};

