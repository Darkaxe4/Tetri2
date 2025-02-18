#include "Includes.hpp"

void Settings::set_value(uint field, uint value)
{
	switch (field)
	{ 
		case 0u:
			return;
		case 1u:
			_music_volume = std::min(value, 100u);
			break;
		case 2u:
			_sfx_volume = std::min(value, 100u);
			break;
		case 3u:
			_max_framerate = std::min(value, 360u);
			break;
		case 4u:
			_video_mode = std::min(size_t(value), sf::VideoMode::getFullscreenModes().size());
			break;
	}
}

json& Settings::to_json()
{
	auto data = json();
	data["music_volume"] = _music_volume;
	data["sfx_volume"] = _sfx_volume;
	data["max_framerate"] = _max_framerate;
	data["video_mode"] = _video_mode;
	return data;
}

void Settings::from_json(json& json)
{
	set_value(1u, json["music_volume"]);
	set_value(2u, json["sfx_volume"]);
	set_value(3u, json["max_framerate"]);
	set_value(4u, json["video_mode"]);
}
