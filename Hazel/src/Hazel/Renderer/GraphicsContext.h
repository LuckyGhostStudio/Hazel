#pragma once

namespace Hazel
{
	/// <summary>
	/// 渲染上下文
	/// </summary>
	class GraphicsContext
	{
	public:
		/// <summary>
		/// 初始化
		/// </summary>
		virtual void Init() = 0;

		/// <summary>
		/// 交换前后缓冲
		/// </summary>
		virtual void SwapBuffers() = 0;
	};
}