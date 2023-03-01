#include "hzpch.h"
#include "OpenGLShader.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
	/// <summary>
	/// �ַ���ת��Ϊ��ɫ������
	/// </summary>
	/// <param name="type">��ɫ����</param>
	/// <returns>��ɫ������</returns>
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") {		//������ɫ��
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel") {	//ƬԪ��ɫ��
			return GL_FRAGMENT_SHADER;
		}

		HZ_CORE_ASSERT(false, "Unknown shader type!");

		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string source = ReadFile(filepath);	//��ȡ��ɫ���ļ�
		auto shaderSources = PreProcess(source);	//���벻ͬ������ɫ��Դ��
		Compile(shaderSources);						//������ɫ��Դ��

		//������ɫ����
		auto lastSlash = filepath.find_last_of("/\\");						//���һ�� / ������
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;		//���һ��/������ ���һ��/����
		auto lastDot = filepath.rfind(".");									//���һ�� . ������
		int count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;	//��ɫ��������
		m_Name = filepath.substr(lastSlash, count);							//��ɫ������
	}
	
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) :m_RendererID(0), m_Name(name)
	{
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;	//��ɫ������-Դ��map
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(shaderSources);						//������ɫ��Դ��
	}

	OpenGLShader::~OpenGLShader()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);	//ɾ����ɫ������
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string result;		//�ļ�����
		std::ifstream in(filepath, std::ios::in | std::ios::binary);	//������ ������

		if (in) {
			in.seekg(0, std::ios::end);			//�ļ�ָ���ƶ����ļ�ĩβ
			result.resize(in.tellg());			//����string��СΪ�ļ���С
			in.seekg(0, std::ios::beg);			//�ļ�ָ���ƶ����ļ���ͷ
			in.read(&result[0], result.size());	//���ļ��� result ��С size
			in.close();							//�ر��ļ�������
		}
		else {
			HZ_CORE_ERROR("Could not open file '{0}'", filepath);	//�޷����ļ�
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

		unsigned int program = glCreateProgram();	//��������;
		HZ_CORE_ASSERT(shaderSources.size() <= 2, "we only support 2 shaders now!");
		std::array<GLenum, 2> glShaderIDs;			//��ɫ��ID�б�

		int shaderIDIndex = 0;
		//��������������ɫ��Դ��
		for (auto& kv : shaderSources) {
			GLenum type = kv.first;					//��ɫ������
			const std::string& source = kv.second;	//��ɫ��Դ��

			unsigned int shader = glCreateShader(type);		//����type������ɫ�� ����id

			const char* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);		//��ɫ��Դ���뷢�͵�GL

			glCompileShader(shader);						//������ɫ��

			int isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);				//��ȡ����״̬
			if (isCompiled == GL_FALSE)	//����ʧ��
			{
				int maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);			//��ȡ������־��Ϣ����

				std::vector<char> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);	//��ȡ������־��Ϣ

				glDeleteShader(shader);	//ɾ����ɫ��

				HZ_CORE_ERROR("{0}", infoLog.data());							//ʧ����Ϣ
				HZ_CORE_ASSERT(false, "Shader Compilation Failure!");			//��ɫ������ʧ��

				break;
			}

			glAttachShader(program, shader);		//����ɫ����ӵ�����
			glShaderIDs[shaderIDIndex++] = shader;	//��ɫ��ID��ӵ��б�
		}

		glLinkProgram(program);		//���ӳ���

		int isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);	//��ȡ����״̬
		if (isLinked == GL_FALSE)	//����ʧ��
		{
			int maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			//ɾ����ɫ��
			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}

			HZ_CORE_ERROR("{0}", infoLog.data());			//ʧ����Ϣ
			HZ_CORE_ASSERT(false, "Shader Link Failure!");	//��ɫ������ʧ��

			return;
		}

		//������ɫ��
		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}

		m_RendererID = program;
	}

	void OpenGLShader::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);		//ʹ����ɫ������
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
		int location = glGetUniformLocation(m_RendererID, name.c_str());	//��ȡUniform����λ��
		glUniform4f(location, value.x, value.y, value.z, value.w);		//���ñ���
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_RendererID, name.c_str());	//��ȡUniform����λ��
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));	//����Uniform������λ�ã������������Ƿ�ת�ã�������ַ��
	}
}