#pragma once

#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
	/// <summary>
	/// OpenGL顶点数组
	/// </summary>
	class OpenGLVertexArray :public VertexArray
	{
	private:
		uint32_t m_RendererID;							//顶点数组id
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;	//绑定在顶点数组的VertexBuffer列表
		Ref<IndexBuffer> m_IndexBuffer;					//绑定在顶点数组的IndexBuffer
		uint32_t m_VertexBufferIndex = 0;
	public:
		OpenGLVertexArray();

		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		/// <summary>
		/// 添加顶点缓冲
		/// </summary>
		/// <param name="vertexBuffer">顶点缓冲</param>
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;

		/// <summary>
		/// 设置顶点索引缓冲
		/// </summary>
		/// <param name="indexBuffer">索引缓冲</param>
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		/// <summary>
		/// 返回VBO列表
		/// </summary>
		/// <returns>顶点缓冲列表</returns>
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }

		/// <summary>
		/// 返回EBO
		/// </summary>
		/// <returns>索引缓冲</returns>
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	};
}