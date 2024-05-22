#pragma once

#include <entt.hpp>
#include "../core.h"

// forward declaration
class Entity;

class ENGINE_API Scene
{
public:
	Scene();
	~Scene();

	Entity CreateEntity(const std::string& name = std::string());
	void DestroyEntity(Entity entity);
	void OnRender();

private:
	entt::registry m_Registry;
	friend class Entity;
};

