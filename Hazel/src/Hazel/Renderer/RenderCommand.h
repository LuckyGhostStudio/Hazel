#pragma once

#include "RendererAPI.h"

namespace Hazel
{
	/// <summary>
	/// ��Ⱦ����
	/// </summary>
	class RenderCommand
	{
	private:
		static RendererAPI* s_RendererAPI;	//��Ⱦ���ӿ�
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		/// <summary>
		/// �����ӿڴ�С
		/// </summary>
		/// <param name="x">����x</param>
		/// <param name="y">����y</param>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		/// <summary>
		/// ����������ɫ
		/// </summary>
		/// <param name="color">������ɫ</param>
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		/// <summary>
		/// ����
		/// </summary>
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		/// <summary>
		/// ��������������
		/// </summary>
		/// <param name="vertexArray">�����ƵĶ�������</param>
		/// <param name="indexCount">��������</param>
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}
	};
}