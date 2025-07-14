#pragma once

struct RenderObject
{
	const sf::Drawable* drawable;
	const sf::RenderStates* states;
	int z_index;
	bool operator < (const RenderObject& other) const {
		return z_index < other.z_index;
	}
};

class BaseScene
{
protected:
	const int index;
	bool initialized;

	std::vector<RenderObject> render_queue;
	entt::registry entity_registry;
	entt::dispatcher dispatcher;
	std::map<std::string, sf::Sprite*> sprite_registry;

	tgui::Group::Ptr gui;

	virtual void bind_input() = 0;
public:
	BaseScene(int index);
	virtual bool load() = 0;
	virtual bool save() = 0;
	inline const int get_index() const { return index; }
	inline auto get_gui() { return gui; }
	virtual void unload() = 0;
	void add_drawable(const sf::Drawable& drawable, int z_index, const sf::RenderStates& states=sf::RenderStates::Default);
	void  remove_drawable(const sf::Drawable& drawable);
	inline auto& get_registry() { return entity_registry; }
	inline auto& get_dispatcher() { return dispatcher; }
	virtual void update(sf::Time elapsed_time) = 0;
	void render(sf::RenderTarget& target, const sf::RenderStates& states);
	~BaseScene(); 
};
