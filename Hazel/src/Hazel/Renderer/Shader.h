#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	/// <summary>
	/// 着色器
	/// </summary>
	class Shader
	{
	public:
		virtual ~Shader() = default;

		/// <summary>
		/// 绑定：使用着色器
		/// </summary>
		virtual void Bind() const = 0;

		/// <summary>
		/// 解除绑定：调试时使用
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
		/// 创建着色器
		/// </summary>
		/// <param name="filepath">着色器文件路径</param>
		/// <returns>着色器</returns>
		static Ref<Shader> Create(const std::string& filepath);

		/// <summary>
		/// 创建着色器
		/// </summary>
		/// <param name="name">着色器名称</param>
		/// <param name="vertexSrc">顶点着色器源代码</param>
		/// <param name="fragmentSrc">片元着色器源代码</param>
		/// <returns>着色器</returns>
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
	};

	/// <summary>
	/// 着色器库
	/// </summary>
	class ShaderLibrary
	{
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;		//着色器map：着色器名-着色器
	public:
		/// <summary>
		/// 添加着色器
		/// </summary>
		/// <param name="name">着色器名</param>
		/// <param name="shader">着色器</param>
		void Add(const std::string& name, const Ref<Shader>& shader);

		/// <summary>
		/// 添加着色器
		/// </summary>
		/// <param name="shader">着色器</param>
		void Add(const Ref<Shader>& shader);

		/// <summary>
		/// 加载着色器
		/// </summary>
		/// <param name="filepath">文件路径</param>
		/// <returns>着色器</returns>
		Ref<Shader> Load(const std::string& filepath);

		/// <summary>
		/// 加载着色器
		/// </summary>
		/// <param name="name">着色器名称</param>
		/// <param name="filepath">文件路径</param>
		/// <returns>着色器</returns>
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		/// <summary>
		/// 返回着色器
		/// </summary>
		/// <param name="name">着色器名称</param>
		/// <returns>着色器</returns>
		Ref<Shader> Get(const std::string& name);

		/// <summary>
		/// 着色器是否存在
		/// </summary>
		/// <param name="name">着色器名</param>
		/// <returns>是否存在</returns>
		bool Exists(const std::string& name) const;
	};
}