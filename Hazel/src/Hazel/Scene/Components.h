#pragma once

#include <glm/glm.hpp>

#include "SceneCamera.h"
#include "ScriptableEntity.h"

namespace Hazel
{
	/// <summary>
	/// ��ǩ���
	/// </summary>
	struct TagComponent
	{
		std::string Tag;	//��ǩ

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) :Tag(tag) {}
	};

	/// <summary>
	/// ת�����
	/// </summary>
	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) :Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	/// <summary>
	/// ͼƬ��Ⱦ�����
	/// </summary>
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) :Color(color) {}
	};

	/// <summary>
	/// ������
	/// </summary>
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;			//�Ƿ��������
		bool FixedAspectRatio = false;	//�Ƿ�̶���߱�

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	/// <summary>
	/// �ű����
	/// </summary>
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;	//�ɽű���ʵ��ʵ�������ڵ��ýű��ڵĺ���

		std::function<void()> InstantiateFunction;		//ʵ��������������ʵ����ScriptableEntity�ű�
		std::function<void()> DestroyInstanceFunction;	//����ʵ����������������ScriptableEntity�ű���ʵ��

		std::function<void(ScriptableEntity*)> OnCreateFunction;			//���ýű�OnCreate�����ĺ���
		std::function<void(ScriptableEntity*)> OnDestroyFunction;			//���ýű�OnDestroy�����ĺ���
		std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;	//���ýű�OnUpdate�����ĺ���

		/// <summary>
		/// ��T���͵Ľű����ű����
		/// </summary>
		/// <typeparam name="T">�ű�����</typeparam>
		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { Instance = new T(); };							//ʵ�����ű���
			DestroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };	//���ٽű����ʵ��

			OnCreateFunction = [](ScriptableEntity* instance) {((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) {((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) {((T*)instance)->OnUpdate(ts); };
		}
	};
}