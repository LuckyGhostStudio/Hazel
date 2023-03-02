#include "hzpch.h"
#include "Scene.h"

#include "Hazel/Renderer/Renderer2D.h"

#include "Components.h"

namespace Hazel
{


	Scene::Scene()
	{
		
	}

	Scene::~Scene()
	{

	}

	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();	//����ʵ��
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