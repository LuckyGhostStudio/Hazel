#pragma once

#include "Hazel/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Hazel
{
	/// <summary>
	/// OpenGL��ɫ��
	/// </summary>
	class OpenGLShader :public Shader
	{
	private:
		uint32_t m_RendererID;	//��ɫ��ID
		std::string m_Name;		//��ɫ������

		/// <summary>
		/// ���ļ�
		/// </summary>
		/// <param name="filepath">�ļ�·��</param>
		/// <returns>�ļ�����</returns>
		std::string ReadFile(const std::string& filepath);

		/// <summary>
		/// Ԥ��������ɫ���ļ�����ͬ��ɫ������
		/// </summary>
		/// <param name="source">��ɫ��Դ����</param>
		/// <returns>��ɫ������-Դ����map</returns>
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		/// <summary>
		/// ������ɫ��
		/// </summary>
		/// <param name="shaderSources">��ɫ������-��ɫ��Դ��map</param>
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
	public:
		/// <summary>
		/// OpenGL��ɫ��
		/// </summary>
		/// <param name="filepath">��ɫ���ļ�·��</param>
		OpenGLShader(const std::string& filepath);

		/// <summary>
		/// OpenGL��ɫ��
		/// </summary>
		/// <param name="vertexSrc">��ɫ����</param>
		/// <param name="vertexSrc">������ɫ��Դ����</param>
		/// <param name="fragmentSrc">Ƭ����ɫ��Դ����</param>
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		/// <summary>
		/// �󶨣�ʹ����ɫ��
		/// </summary>
		virtual void Bind() const override;

		/// <summary>
		/// ����󶨣�����ʱʹ��
		/// </summary>
		virtual void Unbind() const override;

		/// <summary>
		/// ����uniform Int����
		/// </summary>
		/// <param name="name">������</param>
		/// <param name="value">����ֵ</param>
		virtual void SetInt(const std::string& name, int value) override;

		/// <summary>
		/// ����uniform Int Array����
		/// </summary>
		/// <param name="name">������</param>
		/// <param name="values">����ֵ</param>
		/// <param name="count">��������</param>
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		/// <summary>
		/// ����uniform Float����
		/// </summary>
		/// <param name="name">������</param>
		/// <param name="value">����ֵ</param>
		virtual void SetFloat(const std::string& name, float value) override;

		/// <summary>
		/// ����uniform Float3����
		/// </summary>
		/// <param name="name">������</param>
		/// <param name="value">����ֵ</param>
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;

		/// <summary>
		/// ����uniform Float4����
		/// </summary>
		/// <param name="name">������</param>
		/// <param name="value">����ֵ</param>
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

		/// <summary>
		/// ����uniform Matrix4����
		/// </summary>
		/// <param name="name">������</param>
		/// <param name="value">����ֵ</param>
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string GetName() const override { return m_Name; }


		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		/// <summary>
		/// �ϴ�Uniform Mat3����
		/// </summary>
		/// <param name="name">Mat3��shader�еı�����</param>
		/// <param name="matrix">Mat3</param>
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};
}