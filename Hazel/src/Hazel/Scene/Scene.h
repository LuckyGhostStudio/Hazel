#pragma once

#include "entt.hpp"

#include "Hazel/Core/Timestep.h"

namespace Hazel
{
	class Entity;

	/// <summary>
	/// 场景
	/// </summary>
	class Scene
	{
	private:
		friend class Entity;				//友元类Entity
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;

		entt::registry m_Registry;		//实体注册表：实体id集合（unsigned int集合）
		uint32_t m_ViewportWidth = 0;	//场景视口宽
		uint32_t m_ViewportHeight = 0;	//场景视口高
	private:
		/// <summary>
		/// entity添加T组件时调用
		/// </summary>
		/// <typeparam name="T">组件类型</typeparam>
		/// <param name="entity">实体</param>
		/// <param name="component">组件</param>
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	public:
		Scene();
		~Scene();

		/// <summary>
		/// 创建实体
		/// </summary>
		/// <param name="name">实体名</param>
		/// <returns>实体</returns>
		Entity CreateEntity(const std::string& name = std::string());

		/// <summary>
		/// 销毁实体
		/// </summary>
		/// <param name="entity">实体</param>
		void DestroyEntity(Entity entity);

		/// <summary>
		/// 更新：每帧调用
		/// </summary>
		/// <param name="ts">帧间隔</param>
		void OnUpdate(Timestep ts);

		/// <summary>
		/// 重置视口大小：视口改变时调用
		/// </summary>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		void OnViewportResize(uint32_t width, uint32_t height);
	};
}