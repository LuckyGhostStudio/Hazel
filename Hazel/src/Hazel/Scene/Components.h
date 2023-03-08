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
	/// 标签组件
	/// </summary>
	struct TagComponent
	{
		std::string Tag;	//标签

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) :Tag(tag) {}
	};

	/// <summary>
	/// 转换组件
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
		/// 返回Transform矩阵
		/// </summary>
		/// <returns>Transform矩阵</returns>
		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(glm::radians(Rotation)));

			return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	/// <summary>
	/// 图片渲染器组件
	/// </summary>
	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) :Color(color) {}
	};

	/// <summary>
	/// 相机组件
	/// </summary>
	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true;			//是否是主相机
		bool FixedAspectRatio = false;	//是否固定宽高比

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	/// <summary>
	/// 脚本组件
	/// </summary>
	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;	//可脚本化实体实例：用于调用脚本内的函数

		ScriptableEntity* (*InstantiateScript)();	//实例化脚本函数：用来实例化ScriptableEntity脚本

		void (*DestroyScript)(NativeScriptComponent*);	//销毁脚本函数：用来销毁ScriptableEntity脚本的实例

		/// <summary>
		/// 绑定T类型的脚本到脚本组件
		/// </summary>
		/// <typeparam name="T">脚本类型</typeparam>
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };	//实例化脚本类
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };	//销毁脚本类的实例
		}
	};
}