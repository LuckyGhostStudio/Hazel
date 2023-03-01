#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{
	class OpenGLRendererAPI :public RendererAPI
	{
	public:
		/// <summary>
		/// ��ʼ����Ⱦ��
		/// </summary>
		virtual void Init() override;

		/// <summary>
		/// �����ӿڴ�С
		/// </summary>
		/// <param name="x">����x</param>
		/// <param name="y">����y</param>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		/// <summary>
		/// ����������ɫ
		/// </summary>
		/// <param name="color">������ɫ</param>
		virtual void SetClearColor(const glm::vec4& color) override;

		/// <summary>
		/// ����
		/// </summary>
		virtual void Clear() override;

		/// <summary>
		/// ��������������
		/// </summary>
		/// <param name="vertexArray">��������</param>
		/// <param name="indexCount">��������</param>
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}