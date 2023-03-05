#pragma once

#include "Entity.h"

namespace Hazel
{
	/// <summary>
	/// �ɽű���ʵ�壺���б��ؽű��ĸ���
	/// </summary>
	class ScriptableEntity
	{
	private:
		friend class Scene;
		Entity m_Entity;	//�ű����ص�ʵ��
	public:
		virtual ~ScriptableEntity() {}

		/// <summary>
		/// ����T�������
		/// </summary>
		/// <typeparam name="T">�������</typeparam>
		/// <returns>���</returns>
		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		/// <summary>
		/// ʵ�崴��ʱ����
		/// </summary>
		virtual void OnCreate() {}

		/// <summary>
		/// ʵ�崴����ÿ֡����
		/// </summary>
		/// <param name="ts">֡���</param>
		virtual void OnUpdate(Timestep ts) {}

		/// <summary>
		/// ʵ������ʱ����
		/// </summary>
		virtual void OnDestroy() {}
	};
}