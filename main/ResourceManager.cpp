#include "Includes.hpp"

ResourceManager::ResourceManager()
{
}

void ResourceManager::load_resources(path resource_list)
{
	if (resource_list.empty()) return;
	
	auto& json_io = Game::get_json_io();
	auto json_data = json_io.read_json(resource_list);
	
	if (json_data.contains("textures")) {
		for (const auto& texture_data : json_data["textures"]) {
			std::string name = texture_data["name"];
			std::string path = texture_data["path"];
			
			auto* texture = new sf::Texture();
			if (texture->loadFromFile(path)) {
				textures[name] = texture;
			} else {
				delete texture;
			}
		}
	}
	
	if (json_data.contains("soundbanks")) {
		for (const auto& soundbank_data : json_data["soundbanks"]) {
			std::string name = soundbank_data["name"];
			wchar_t path = soundbank_data["path"];
			
			Game::get_sound_manager().load_soundbank(&path);
		}
	}
}

sf::Texture* ResourceManager::get_texture(std::string_view name)
{
	auto it = textures.find(std::string(name));
	return (it != textures.end()) ? it->second : nullptr;
}

ResourceManager::~ResourceManager()
{
	for (auto& it : textures)
	{
		delete it.second;
	}
}