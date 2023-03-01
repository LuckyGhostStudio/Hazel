#include "hzpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
	/// <summary>
	/// 字符串转换为着色器类型
	/// </summary>
	/// <param name="type">着色器名</param>
	/// <returns>着色器类型</returns>
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") {		//顶点着色器
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel") {	//片元着色器
			return GL_FRAGMENT_SHADER;
		}

		HZ_CORE_ASSERT(false, "Unknown shader type!");

		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);	//读取着色器文件
		auto shaderSources = PreProcess(source);	//分离不同类型着色器源码
		Compile(shaderSources);						//编译着色器源码

		//计算着色器名
		auto lastSlash = filepath.find_last_of("/\\");						//最后一个 / 的索引
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;		//最后一个/不存在 最后一个/存在
		auto lastDot = filepath.rfind(".");									//最后一个 . 的索引
		int count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;	//着色器名长度
		m_Name = filepath.substr(lastSlash, count);							//着色器名称
	}
	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) :m_RendererID(0), m_Name(name)
	{
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;	//着色器类型-源码map
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);						//编译着色器源码
	}

	OpenGLShader::~OpenGLShader()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);	//删除着色器程序
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string result;		//文件内容
		std::ifstream in(filepath, std::ios::in | std::ios::binary);	//输入流 二进制

		if (in) {
			in.seekg(0, std::ios::end);			//文件指针移动到文件末尾
			result.resize(in.tellg());			//重置string大小为文件大小
			in.seekg(0, std::ios::beg);			//文件指针移动到文件开头
			in.read(&result[0], result.size());	//读文件到 result 大小 size
			in.close();							//关闭文件输入流
		}
		else {
			HZ_CORE_ERROR("Could not open file '{0}'", filepath);	//无法打开文件
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			HZ_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaderSources)
	{
		HZ_PROFILE_FUNCTION();

		unsigned int program = glCreateProgram();	//创建程序;
		HZ_CORE_ASSERT(shaderSources.size() <= 2, "we only support 2 shaders now!");
		std::array<GLenum, 2> glShaderIDs;			//着色器ID列表

		int shaderIDIndex = 0;
		//遍历所有类型着色器源码
		for (auto& kv : shaderSources) {
			GLenum type = kv.first;					//着色器类型
			const std::string& source = kv.second;	//着色器源码

			unsigned int shader = glCreateShader(type);		//创建type类型着色器 返回id

			const char* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);		//着色器源代码发送到GL

			glCompileShader(shader);						//编译着色器

			int isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);				//获取编译状态
			if (isCompiled == GL_FALSE)	//编译失败
			{
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);			//获取编译日志信息长度

				std::vector<char> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);	//获取编译日志信息

				glDeleteShader(shader);	//删除着色器

				HZ_CORE_ERROR("{0}", infoLog.data());							//失败信息
				HZ_CORE_ASSERT(false, "Shader Compilation Failure!");			//着色器编译失败

				break;
			}

			glAttachShader(program, shader);		//将着色器添加到程序
			glShaderIDs[shaderIDIndex++] = shader;	//着色器ID添加到列表
		}

		glLinkProgram(program);		//链接程序

		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);	//获取链接状态
		if (isLinked == GL_FALSE)	//链接失败
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			//删除着色器
			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}

			HZ_CORE_ERROR("{0}", infoLog.data());			//失败信息
			HZ_CORE_ASSERT(false, "Shader Link Failure!");	//着色器链接失败

			return;
		}

		//分离着色器
		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}

		m_RendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);		//使用着色器程序
	}

	void OpenGLShader::Unbind() const
	{
		HZ_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());	//获取Uniform变量位置
		glUniform4f(location, value.x, value.y, value.z, value.w);		//设置变量
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());	//获取Uniform变量位置
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));	//设置Uniform变量（位置，变量个数，是否转置，变量地址）
	}
}