#pragma once

#include <memory>
#include "Hazel/Renderer/Buffer.h"

namespace Hazel
{
	/// <summary>
	/// ��������
	/// </summary>
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		/// <summary>
		/// ��Ӷ��㻺��
		/// </summary>
		/// <param name="vertexBuffer">���㻺��</param>
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;

		/// <summary>
		/// ���ö�����������
		/// </summary>
		/// <param name="indexBuffer">��������</param>
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

		/// <summary>
		/// ����VBO�б�
		/// </summary>
		/// <returns>���㻺���б�</returns>
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		/// <summary>
		/// ����EBO
		/// </summary>
		/// <returns>��������</returns>
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		/// <summary>
		/// ���������������
		/// </summary>
		/// <returns>��������</returns>
		static Ref<VertexArray> Create();
	};
}