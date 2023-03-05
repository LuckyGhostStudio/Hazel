#pragma once

#include <glm/glm.hpp>

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
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) :Transform(transform) {}

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
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

		std::function<void()> InstantiateFunction;		//实例化函数：用来实例化ScriptableEntity脚本
		std::function<void()> DestroyInstanceFunction;	//销毁实例函数：用来销毁ScriptableEntity脚本的实例

		std::function<void(ScriptableEntity*)> OnCreateFunction;			//调用脚本OnCreate函数的函数
		std::function<void(ScriptableEntity*)> OnDestroyFunction;			//调用脚本OnDestroy函数的函数
		std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;	//调用脚本OnUpdate函数的函数

		/// <summary>
		/// 绑定T类型的脚本到脚本组件
		/// </summary>
		/// <typeparam name="T">脚本类型</typeparam>
		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() { Instance = new T(); };							//实例化脚本类
			DestroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };	//销毁脚本类的实例

			OnCreateFunction = [](ScriptableEntity* instance) {((T*)instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) {((T*)instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) {((T*)instance)->OnUpdate(ts); };
		}
	};
}