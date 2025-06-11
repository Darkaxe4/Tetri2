#pragma once
class Settings : public I_JSONSerializable
{
private:
	using uint = unsigned int;

	short unsigned int _music_volume;
	short unsigned int _sfx_volume;
	uint _max_framerate;
	uint _video_mode;
public:
	Settings() :
		_music_volume(100),
		_sfx_volume(100),
		_max_framerate(0),
		_video_mode(0) { };

	void set_value(uint field, uint value);

	// Inherited via I_JSONSerializable
	virtual json to_json() const override;

	virtual void from_json(const json& json) override;

};

