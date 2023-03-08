#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

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
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& position) :Position(position) {}

		/// <summary>
		/// ����Transform����
		/// </summary>
		/// <returns>Transform����</returns>
		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(Rotation)));

			return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
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

		ScriptableEntity* (*InstantiateScript)();	//ʵ�����ű�����������ʵ����ScriptableEntity�ű�

		void (*DestroyScript)(NativeScriptComponent*);	//���ٽű���������������ScriptableEntity�ű���ʵ��

		/// <summary>
		/// ��T���͵Ľű����ű����
		/// </summary>
		/// <typeparam name="T">�ű�����</typeparam>
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };	//ʵ�����ű���
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };	//���ٽű����ʵ��
		}
	};
}