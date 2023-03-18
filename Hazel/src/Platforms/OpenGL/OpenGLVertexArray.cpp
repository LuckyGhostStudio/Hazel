#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hazel
{
	/// <summary>
	/// ShaderDataTypeת��ΪOpenGL��������
	/// </summary>
	/// <param name="">ShaderDataType</param>
	/// <returns>OpenGL��������</returns>
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Hazel::ShaderDataType::Float:	return GL_FLOAT;
			case Hazel::ShaderDataType::Float2:	return GL_FLOAT;
			case Hazel::ShaderDataType::Float3:	return GL_FLOAT;
			case Hazel::ShaderDataType::Float4:	return GL_FLOAT;
			case Hazel::ShaderDataType::Mat3:	return GL_FLOAT;
			case Hazel::ShaderDataType::Mat4:	return GL_FLOAT;
			case Hazel::ShaderDataType::Int:	return GL_INT;
			case Hazel::ShaderDataType::Int2:	return GL_INT;
			case Hazel::ShaderDataType::Int3:	return GL_INT;
			case Hazel::ShaderDataType::Int4:	return GL_INT;
			case Hazel::ShaderDataType::Bool:	return GL_BOOL;
		}

		HZ_CORE_ASSERT(false, "Unknow ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		HZ_PROFILE_FUNCTION();

		glCreateVertexArrays(1, &m_RendererID);	//������������
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);	//ɾ����������
	}
	
	void OpenGLVertexArray::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);	//�󶨶�������
	}
	
	void OpenGLVertexArray::Unbind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(0);	//�����
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");	//����Ԫ��Ϊ��

		glBindVertexArray(m_RendererID);	//�󶨶�������
		vertexBuffer->Bind();				//��VBO��VAO

		//���ö��㻺��������
		const auto& layout = vertexBuffer->GetLayout();			//���㻺��������

		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);		//���ö�������

				glVertexAttribPointer(m_VertexBufferIndex,			//��������λ�ñ��
					element.GetComponentCount(),					//�����������ݸ���
					ShaderDataTypeToOpenGLBaseType(element.Type), 	//��������
					element.Normalized ? GL_TRUE : GL_FALSE, 		//�Ƿ��׼��
					layout.GetStride(), 							//�����С���ֽڣ�
					(const void*)element.Offset);					//��������ƫ�������ֽڣ�

				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribIPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);

				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
			}
		}

		m_VertexBuffers.push_back(vertexBuffer);	//���VBO���б�
	}
	
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);	//�󶨶�������
		indexBuffer->Bind();				//��EBO��VAO

		m_IndexBuffer = indexBuffer;		//����EBO
	}
}