#pragma once

#include "Scene.h"

namespace Hazel
{
	/// <summary>
	/// �������л���
	/// </summary>
	class SceneSerializer
	{
	private:
		Ref<Scene> m_Scene;	//����
	public:
		/// <summary>
		/// �������л���
		/// </summary>
		/// <param name="scene">����</param>
		SceneSerializer(const Ref<Scene> scene);

		/// <summary>
		/// ���л����������л�Ϊ�ı��ļ�
		/// </summary>
		/// <param name="filepath">�ļ����·��</param>
		void Serialize(const std::string& filepath);

		/// <summary>
		/// ����ʱ���л����������л�Ϊ������
		/// </summary>
		/// <param name="filepath">�ļ����·��</param>
		void SerializeRuntime(const std::string& filepath);

		/// <summary>
		/// �����л��������ı��ļ������л�
		/// </summary>
		/// <param name="filepath">�ļ�·��</param>
		/// <returns>���</returns>
		bool Deserialize(const std::string& filepath);

		/// <summary>
		/// ����ʱ�����л��������Ʒ����л�
		/// </summary>
		/// <param name="filepath">�ļ�·��</param>
		/// <returns>���</returns>
		bool DeserializeRuntime(const std::string& filepath);
	};
}