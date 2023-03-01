#pragma once

#include "Hazel/Renderer/RendererAPI.h"

namespace Hazel
{
	class OpenGLRendererAPI :public RendererAPI
	{
	public:
		/// <summary>
		/// 初始化渲染器
		/// </summary>
		virtual void Init() override;

		/// <summary>
		/// 设置视口大小
		/// </summary>
		/// <param name="x">左下x</param>
		/// <param name="y">左下y</param>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		/// <summary>
		/// 设置清屏颜色
		/// </summary>
		/// <param name="color">清屏颜色</param>
		virtual void SetClearColor(const glm::vec4& color) override;

		/// <summary>
		/// 清屏
		/// </summary>
		virtual void Clear() override;

		/// <summary>
		/// 绘制索引缓冲区
		/// </summary>
		/// <param name="vertexArray">顶点数组</param>
		/// <param name="indexCount">索引个数</param>
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};
}