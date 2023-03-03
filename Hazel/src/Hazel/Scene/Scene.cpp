#include "hzpch.h"
#include "Scene.h"

#include "Hazel/Renderer/Renderer2D.h"

#include "Components.h"
#include "Entity.h"

namespace Hazel
{


	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };		//创建实体
		entity.AddComponent<TransformComponent>();			//添加Transform组件（默认组件）
		auto& tag = entity.AddComponent<TagComponent>();	//添加Tag组件（默认组件）
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}
	
	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

		for (auto entity : group) {
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}
}