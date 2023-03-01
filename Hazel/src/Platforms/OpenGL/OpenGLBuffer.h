#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	private:
		uint32_t m_RendererID;		//���㻺��ID
		BufferLayout m_Layout;		//���㻺��������
	public:
		/// <summary>
		/// ���㻺����
		/// </summary>
		/// <param name="size">�����С</param>
		/// <returns>���㻺��</returns>
		OpenGLVertexBuffer(uint32_t size);

		/// <summary>
		/// ���㻺����
		/// </summary>
		/// <param name="vertices">��������</param>
		/// <param name="size">�����С</param>
		/// <returns>���㻺��</returns>
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		/// <summary>
		/// ���ö��㻺��������
		/// </summary>
		/// <param name="data">����</param>
		/// <param name="size">��С���ֽڣ�</param>
		virtual void SetData(const void* data, uint32_t size) override;
			
		/// <summary>
		/// ���ض��㻺��������
		/// </summary>
		/// <returns>���㻺��������</returns>
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		/// <summary>
		/// ���ö��㻺�岼��
		/// </summary>
		/// <param name="layout">���㻺�沼��</param>
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	private:
		uint32_t m_RendererID;		//��������ID
		uint32_t m_Count;			//��������
	public:
		/// <summary>
		/// ��������������
		/// </summary>
		/// <param name="vertices">��������</param>
		/// <param name="count">��������</param>
		/// <returns>��������</returns>
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		/// <summary>
		/// ������������
		/// </summary>
		/// <returns>��������</returns>
		virtual uint32_t GetCount() const { return m_Count; }
	};
}