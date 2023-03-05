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
	};
}