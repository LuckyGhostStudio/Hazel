#pragma once

#include <glm/glm.hpp>

#include "SceneCamera.h"

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
}