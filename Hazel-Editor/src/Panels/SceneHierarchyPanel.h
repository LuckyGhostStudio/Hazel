#pragma once

#include "Hazel/Scene/Scene.h"
#include "Hazel/Core/Core.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Scene/Entity.h"

namespace Hazel
{
	/// <summary>
	/// ��������㼶���
	/// </summary>
	class SceneHierarchyPanel
	{
	private:
		Ref<Scene> m_Context;		//�����ʾ�ĳ���
		Entity m_SelectionContext;	//��ѡ�е�ʵ��

		/// <summary>
		/// ����ʵ����
		/// </summary>
		/// <param name="entity">ʵ��</param>
		void DrawEntityNode(Entity entity);

		/// <summary>
		/// ����ʵ����������
		/// </summary>
		/// <param name="entity">ʵ��</param>
		void DrawComponents(Entity entity);
	public:
		SceneHierarchyPanel() = default;

		/// <summary>
		/// ��������㼶���
		/// </summary>
		/// <param name="context">�����ģ�������</param>
		SceneHierarchyPanel(const Ref<Scene>& context);

		/// <summary>
		/// ����������
		/// </summary>
		/// <param name="context">�����ģ�������</param>
		void SetContext(const Ref<Scene>& context);

		/// <summary>
		/// ��ȾImGui
		/// </summary>
		void OnImGuiRender();

		/// <summary>
		/// ���ر�ѡ������
		/// </summary>
		/// <returns>��ѡ������</returns>
		Entity GetSelectedEntity() const { return m_SelectionContext; }
	};
}