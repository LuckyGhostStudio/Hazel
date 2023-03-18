#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Hazel
{
	/// <summary>
	/// ShaderDataType转换为OpenGL基本类型
	/// </summary>
	/// <param name="">ShaderDataType</param>
	/// <returns>OpenGL基本类型</returns>
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

		glCreateVertexArrays(1, &m_RendererID);	//创建顶点数组
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererID);	//删除顶点数组
	}
	
	void OpenGLVertexArray::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);	//绑定顶点数组
	}
	
	void OpenGLVertexArray::Unbind() const
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(0);	//解除绑定
	}
	
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");	//布局元素为零

		glBindVertexArray(m_RendererID);	//绑定顶点数组
		vertexBuffer->Bind();				//绑定VBO到VAO

		//设置顶点缓冲区布局
		const auto& layout = vertexBuffer->GetLayout();			//顶点缓冲区布局

		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);		//启用顶点属性

				glVertexAttribPointer(m_VertexBufferIndex,			//顶点属性位置编号
					element.GetComponentCount(),					//顶点属性数据个数
					ShaderDataTypeToOpenGLBaseType(element.Type), 	//数据类型
					element.Normalized ? GL_TRUE : GL_FALSE, 		//是否标准化
					layout.GetStride(), 							//顶点大小（字节）
					(const void*)element.Offset);					//顶点属性偏移量（字节）

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

		m_VertexBuffers.push_back(vertexBuffer);	//添加VBO到列表
	}
	
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		HZ_PROFILE_FUNCTION();

		glBindVertexArray(m_RendererID);	//绑定顶点数组
		indexBuffer->Bind();				//绑定EBO到VAO

		m_IndexBuffer = indexBuffer;		//设置EBO
	}
}