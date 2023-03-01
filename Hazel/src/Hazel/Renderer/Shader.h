#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	/// <summary>
	/// ��ɫ��
	/// </summary>
	class Shader
	{
	public:
		virtual ~Shader() = default;

		/// <summary>
		/// �󶨣�ʹ����ɫ��
		/// </summary>
		virtual void Bind() const = 0;

		/// <summary>
		/// ����󶨣�����ʱʹ��
		/// </summary>
		virtual void Unbind() const = 0;


		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const std::string GetName() const = 0;

		/// <summary>
		/// ������ɫ��
		/// </summary>
		/// <param name="filepath">��ɫ���ļ�·��</param>
		/// <returns>��ɫ��</returns>
		static Ref<Shader> Create(const std::string& filepath);

		/// <summary>
		/// ������ɫ��
		/// </summary>
		/// <param name="name">��ɫ������</param>
		/// <param name="vertexSrc">������ɫ��Դ����</param>
		/// <param name="fragmentSrc">ƬԪ��ɫ��Դ����</param>
		/// <returns>��ɫ��</returns>
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	/// <summary>
	/// ��ɫ����
	/// </summary>
	class ShaderLibrary
	{
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;		//��ɫ��map����ɫ����-��ɫ��
	public:
		/// <summary>
		/// �����ɫ��
		/// </summary>
		/// <param name="name">��ɫ����</param>
		/// <param name="shader">��ɫ��</param>
		void Add(const std::string& name, const Ref<Shader>& shader);

		/// <summary>
		/// �����ɫ��
		/// </summary>
		/// <param name="shader">��ɫ��</param>
		void Add(const Ref<Shader>& shader);

		/// <summary>
		/// ������ɫ��
		/// </summary>
		/// <param name="filepath">�ļ�·��</param>
		/// <returns>��ɫ��</returns>
		Ref<Shader> Load(const std::string& filepath);

		/// <summary>
		/// ������ɫ��
		/// </summary>
		/// <param name="name">��ɫ������</param>
		/// <param name="filepath">�ļ�·��</param>
		/// <returns>��ɫ��</returns>
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		/// <summary>
		/// ������ɫ��
		/// </summary>
		/// <param name="name">��ɫ������</param>
		/// <returns>��ɫ��</returns>
		Ref<Shader> Get(const std::string& name);

		/// <summary>
		/// ��ɫ���Ƿ����
		/// </summary>
		/// <param name="name">��ɫ����</param>
		/// <returns>�Ƿ����</returns>
		bool Exists(const std::string& name) const;
	};
}