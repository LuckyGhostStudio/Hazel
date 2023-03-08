#pragma once

#include "entt.hpp"

#include "Hazel/Core/Timestep.h"

namespace Hazel
{
	class Entity;

	/// <summary>
	/// ����
	/// </summary>
	class Scene
	{
	private:
		friend class Entity;				//��Ԫ��Entity
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;

		entt::registry m_Registry;		//ʵ��ע���ʵ��id���ϣ�unsigned int���ϣ�
		uint32_t m_ViewportWidth = 0;	//�����ӿڿ�
		uint32_t m_ViewportHeight = 0;	//�����ӿڸ�
	private:
		/// <summary>
		/// entity���T���ʱ����
		/// </summary>
		/// <typeparam name="T">�������</typeparam>
		/// <param name="entity">ʵ��</param>
		/// <param name="component">���</param>
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	public:
		Scene();
		~Scene();

		/// <summary>
		/// ����ʵ��
		/// </summary>
		/// <param name="name">ʵ����</param>
		/// <returns>ʵ��</returns>
		Entity CreateEntity(const std::string& name = std::string());

		/// <summary>
		/// ����ʵ��
		/// </summary>
		/// <param name="entity">ʵ��</param>
		void DestroyEntity(Entity entity);

		/// <summary>
		/// ���£�ÿ֡����
		/// </summary>
		/// <param name="ts">֡���</param>
		void OnUpdate(Timestep ts);

		/// <summary>
		/// �����ӿڴ�С���ӿڸı�ʱ����
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		void OnViewportResize(uint32_t width, uint32_t height);
	};
}