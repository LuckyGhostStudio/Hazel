#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Hazel
{
	/// <summary>
	/// ��Ⱦ���ӿ�
	/// </summary>
	class RendererAPI
	{
	public:
		/// <summary>
		/// �ӿ�
		/// </summary>
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual void Init() = 0;

		/// <summary>
		/// �����ӿڴ�С
		/// </summary>
		/// <param name="x">����x</param>
		/// <param name="y">����y</param>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/// <summary>
		/// ����������ɫ
		/// </summary>
		/// <param name="color">������ɫ</param>
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/// <summary>
		/// ����
		/// </summary>
		virtual void Clear() = 0;

		/// <summary>
		/// ��������������
		/// </summary>
		/// <param name="vertexArray">��������</param>
		/// <param name="indexCount">��������</param>
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;	//��Ⱦ�ӿ�
	};
}