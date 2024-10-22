#include "scene.h"
#include "components.h"
#include <glm.hpp>
#include "../rendering/opengl_pipeline.h"
#include <iostream>
#include "entity.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

Entity Scene::CreateEntity(const std::string& name)
{
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	auto& tag = entity.AddComponent<TagComponent>();
	tag.Tag = name.empty() ? "Entity" : name;
	return entity;
}

void Scene::DestroyEntity(Entity entity)
{
	/*m_Registry.destroy(entity);*/
}

void Scene::OnRender()
{
}
