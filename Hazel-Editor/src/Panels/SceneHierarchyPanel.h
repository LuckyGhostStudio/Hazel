#pragma once

#include "Hazel/Scene/Scene.h"
#include "Hazel/Core/Core.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Scene/Entity.h"

namespace Hazel
{
	/// <summary>
	/// 场景对象层级面板
	/// </summary>
	class SceneHierarchyPanel
	{
	private:
		Ref<Scene> m_Context;		//面板显示的场景
		Entity m_SelectionContext;	//被选择中实体

		/// <summary>
		/// 绘制实体结点
		/// </summary>
		/// <param name="entity">实体</param>
		void DrawEntityNode(Entity entity);
	public:
		SceneHierarchyPanel() = default;

		/// <summary>
		/// 场景对象层级面板
		/// </summary>
		/// <param name="context">上下文（场景）</param>
		SceneHierarchyPanel(const Ref<Scene>& context);

		/// <summary>
		/// 设置上下文
		/// </summary>
		/// <param name="context">上下文（场景）</param>
		void SetContext(const Ref<Scene>& context);

		/// <summary>
		/// 渲染ImGui
		/// </summary>
		void OnImGuiRender();
	};
}