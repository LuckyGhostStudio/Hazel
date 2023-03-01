#pragma once

#include "RendererAPI.h"

namespace Hazel
{
	/// <summary>
	/// 渲染命令
	/// </summary>
	class RenderCommand
	{
	private:
		static RendererAPI* s_RendererAPI;	//渲染器接口
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		/// <summary>
		/// 设置视口大小
		/// </summary>
		/// <param name="x">左下x</param>
		/// <param name="y">左下y</param>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		/// <summary>
		/// 设置清屏颜色
		/// </summary>
		/// <param name="color">清屏颜色</param>
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		/// <summary>
		/// 清屏
		/// </summary>
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		/// <summary>
		/// 绘制索引缓冲区
		/// </summary>
		/// <param name="vertexArray">待绘制的顶点数组</param>
		/// <param name="indexCount">索引个数</param>
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, indexCount);
		}
	};
}