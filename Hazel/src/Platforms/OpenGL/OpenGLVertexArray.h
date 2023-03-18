#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
	/// <summary>
	/// OpenGL��������
	/// </summary>
	class OpenGLVertexArray :public VertexArray
	{
	private:
		uint32_t m_RendererID;							//��������id
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;	//���ڶ��������VertexBuffer�б�
		Ref<IndexBuffer> m_IndexBuffer;					//���ڶ��������IndexBuffer
		uint32_t m_VertexBufferIndex = 0;
	public:
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		/// <summary>
		/// ��Ӷ��㻺��
		/// </summary>
		/// <param name="vertexBuffer">���㻺��</param>
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

		/// <summary>
		/// ���ö�����������
		/// </summary>
		/// <param name="indexBuffer">��������</param>
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		/// <summary>
		/// ����VBO�б�
		/// </summary>
		/// <returns>���㻺���б�</returns>
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }

		/// <summary>
		/// ����EBO
		/// </summary>
		/// <returns>��������</returns>
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	};
}