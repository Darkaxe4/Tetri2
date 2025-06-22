#pragma once
class SystemManager
{
private:
	std::vector<BaseSystem*> systems;

public:
	void load_systems();
	void register_system(BaseSystem* system);
	void update_systems(sf::Time dt);
	~SystemManager();
};

