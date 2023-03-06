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
		Entity entity = { m_Registry.create(), this };		//����ʵ��
		entity.AddComponent<TransformComponent>();			//���Transform�����Ĭ�������
		auto& tag = entity.AddComponent<TagComponent>();	//���Tag�����Ĭ�������
		tag.Tag = name.empty() ? "Entity" : name;

		return entity;
	}
	
	void Scene::OnUpdate(Timestep ts)
	{
		//��������ӵ�нű������ʵ�壬����each�ڵĺ���
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, NativeScriptComponent& nsc)
		{
			//�ű�δʵ����
			if (!nsc.Instance) {
				nsc.Instance = nsc.InstantiateScript();				//ʵ�����ű�
				nsc.Instance->m_Entity = Entity{ entity, this };	//���ýű�������ʵ��

				nsc.Instance->OnCreate();	//���ýű���OnCreate����
			}
			nsc.Instance->OnUpdate(ts);		//���ýű���OnOpdate����
		});

		Camera* mainCamera = nullptr;	//�����
		glm::mat4 cameraTransform;

		auto view = m_Registry.view<TransformComponent, CameraComponent>();	//��Transform��Camera������ʵ��

		for (auto entity : view) {
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			//�ҵ������
			if (camera.Primary) {
				mainCamera = &camera.Camera;
				cameraTransform = transform.GetTransform();
				break;
			}
		}

		//���������
		if (mainCamera) {
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);

			for (auto entity : group) {
				auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}
	
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		auto view = m_Registry.view<CameraComponent>();	//������Camera�����ʵ��

		for (auto entity : view) {
			auto& cameraComponent = view.get<CameraComponent>(entity);	//���Camerae���
			//���ǹ̶���߱�
			if (!cameraComponent.FixedAspectRatio) {
				cameraComponent.Camera.SetViewportSize(width, height);	//�����ӿڴ�С
			}
		}
	}
}