#pragma once

#include <memory>
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	/// <summary>
	/// 顶点数组
	/// </summary>
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		/// <summary>
		/// 添加顶点缓冲
		/// </summary>
		/// <param name="vertexBuffer">顶点缓冲</param>
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

		/// <summary>
		/// 设置顶点索引缓冲
		/// </summary>
		/// <param name="indexBuffer">索引缓冲</param>
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		/// <summary>
		/// 返回VBO列表
		/// </summary>
		/// <returns>顶点缓冲列表</returns>
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		/// <summary>
		/// 返回EBO
		/// </summary>
		/// <returns>索引缓冲</returns>
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		/// <summary>
		/// 创建顶点数组对象
		/// </summary>
		/// <returns>顶点数组</returns>
		static Ref<VertexArray> Create();
	};
}