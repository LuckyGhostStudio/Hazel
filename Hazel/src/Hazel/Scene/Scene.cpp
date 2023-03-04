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
		Camera* mainCamera = nullptr;	//主相机
		glm::mat4* cameraTransform = nullptr;

		auto view = m_Registry.view<TransformComponent, CameraComponent>();	//有Transform和Camera的所有实体

		for (auto entity : view) {
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			//找到主相机
			if (camera.Primary) {
				mainCamera = &camera.Camera;
				cameraTransform = &transform.Transform;
				break;
			}
		}

		//主相机存在
		if (mainCamera) {
			Renderer2D::BeginScene(*mainCamera, *cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for (auto entity : group) {
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform, sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}
	
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();	//所有有Camera组件的实体

		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);	//获得Camerae组件
			//不是固定宽高比
			if (!cameraComponent.FixedAspectRatio) {
				cameraComponent.Camera.SetViewportSize(width, height);	//设置视口大小
			}
		}
	}
}