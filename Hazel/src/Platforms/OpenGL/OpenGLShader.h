#pragma once

#include "Hazel/Renderer/Shader.h"

#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace Hazel
{
	/// <summary>
	/// OpenGL着色器
	/// </summary>
	class OpenGLShader :public Shader
	{
	private:
		uint32_t m_RendererID;	//着色器ID
		std::string m_Name;		//着色器名字

		/// <summary>
		/// 读文件
		/// </summary>
		/// <param name="filepath">文件路径</param>
		/// <returns>文件内容</returns>
		std::string ReadFile(const std::string& filepath);

		/// <summary>
		/// 预处理：将着色器文件按不同着色器分离
		/// </summary>
		/// <param name="source">着色器源代码</param>
		/// <returns>着色器类型-源代码map</returns>
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);

		/// <summary>
		/// 编译着色器
		/// </summary>
		/// <param name="shaderSources">着色器类型-着色器源码map</param>
		void Compile(std::unordered_map<GLenum, std::string>& shaderSources);
	public:
		/// <summary>
		/// OpenGL着色器
		/// </summary>
		/// <param name="filepath">着色器文件路径</param>
		OpenGLShader(const std::string& filepath);

		/// <summary>
		/// OpenGL着色器
		/// </summary>
		/// <param name="vertexSrc">着色器名</param>
		/// <param name="vertexSrc">顶点着色器源代码</param>
		/// <param name="fragmentSrc">片段着色器源代码</param>
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		/// <summary>
		/// 绑定：使用着色器
		/// </summary>
		virtual void Bind() const override;

		/// <summary>
		/// 解除绑定：调试时使用
		/// </summary>
		virtual void Unbind() const override;

		/// <summary>
		/// 设置uniform Int变量
		/// </summary>
		/// <param name="name">变量名</param>
		/// <param name="value">变量值</param>
		virtual void SetInt(const std::string& name, int value) override;

		/// <summary>
		/// 设置uniform Int Array变量
		/// </summary>
		/// <param name="name">变量名</param>
		/// <param name="values">变量值</param>
		/// <param name="count">变量个数</param>
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;

		/// <summary>
		/// 设置uniform Float变量
		/// </summary>
		/// <param name="name">变量名</param>
		/// <param name="value">变量值</param>
		virtual void SetFloat(const std::string& name, float value) override;

		/// <summary>
		/// 设置uniform Float3变量
		/// </summary>
		/// <param name="name">变量名</param>
		/// <param name="value">变量值</param>
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;

		/// <summary>
		/// 设置uniform Float4变量
		/// </summary>
		/// <param name="name">变量名</param>
		/// <param name="value">变量值</param>
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;

		/// <summary>
		/// 设置uniform Matrix4变量
		/// </summary>
		/// <param name="name">变量名</param>
		/// <param name="value">变量值</param>
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		virtual const std::string GetName() const override { return m_Name; }


		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		/// <summary>
		/// 上传Uniform Mat3变量
		/// </summary>
		/// <param name="name">Mat3在shader中的变量名</param>
		/// <param name="matrix">Mat3</param>
		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	};
}