#pragma once

#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	class OpenGLVertexBuffer :public VertexBuffer
	{
	private:
		uint32_t m_RendererID;		//顶点缓冲ID
		BufferLayout m_Layout;		//顶点缓冲区布局
	public:
		/// <summary>
		/// 顶点缓冲区
		/// </summary>
		/// <param name="size">顶点大小</param>
		/// <returns>顶点缓冲</returns>
		OpenGLVertexBuffer(uint32_t size);

		/// <summary>
		/// 顶点缓冲区
		/// </summary>
		/// <param name="vertices">顶点数据</param>
		/// <param name="size">顶点大小</param>
		/// <returns>顶点缓冲</returns>
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		/// <summary>
		/// 设置顶点缓冲区数据
		/// </summary>
		/// <param name="data">数据</param>
		/// <param name="size">大小（字节）</param>
		virtual void SetData(const void* data, uint32_t size) override;
			
		/// <summary>
		/// 返回顶点缓冲区布局
		/// </summary>
		/// <returns>顶点缓冲区布局</returns>
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }

		/// <summary>
		/// 设置顶点缓冲布局
		/// </summary>
		/// <param name="layout">顶点缓存布局</param>
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	private:
		uint32_t m_RendererID;		//索引缓冲ID
		uint32_t m_Count;			//索引个数
	public:
		/// <summary>
		/// 创建索引缓冲区
		/// </summary>
		/// <param name="vertices">索引数据</param>
		/// <param name="count">索引个数</param>
		/// <returns>索引缓冲</returns>
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		/// <summary>
		/// 返回索引个数
		/// </summary>
		/// <returns>索引个数</returns>
		virtual uint32_t GetCount() const { return m_Count; }
	};
}