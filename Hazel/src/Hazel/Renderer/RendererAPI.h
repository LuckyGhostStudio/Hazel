#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Hazel
{
	/// <summary>
	/// 渲染器接口
	/// </summary>
	class RendererAPI
	{
	public:
		/// <summary>
		/// 接口
		/// </summary>
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual void Init() = 0;

		/// <summary>
		/// 设置视口大小
		/// </summary>
		/// <param name="x">左下x</param>
		/// <param name="y">左下y</param>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		/// <summary>
		/// 设置清屏颜色
		/// </summary>
		/// <param name="color">清屏颜色</param>
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/// <summary>
		/// 清屏
		/// </summary>
		virtual void Clear() = 0;

		/// <summary>
		/// 绘制索引缓冲区
		/// </summary>
		/// <param name="vertexArray">顶点数组</param>
		/// <param name="indexCount">索引个数</param>
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;	//渲染接口
	};
}