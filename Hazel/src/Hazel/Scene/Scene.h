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
		friend class Entity;	//��Ԫ��Entity

		entt::registry m_Registry;	//ʵ��ע���ʵ��id���ϣ�unsigned int���ϣ�
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
		/// ���£�ÿ֡����
		/// </summary>
		/// <param name="ts">֡���</param>
		void OnUpdate(Timestep ts);
	};
}