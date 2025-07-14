#pragma once


class ResourceManager
{
private:
	using path = std::filesystem::path;
	std::unordered_map<std::string, sf::Texture*> textures;
public:
	ResourceManager();
	void load_resources(path resource_list = path{});
	sf::Texture* get_texture(std::string_view name);
	~ResourceManager();
};
