#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{
	/// <summary>
	/// OpenGL上下文
	/// </summary>
	class OpenGLContext :public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;		//窗口句柄

	public:
		/// <summary>
		/// OpenGL上下文
		/// </summary>
		/// <param name="windowHandle">窗口句柄</param>
		OpenGLContext(GLFWwindow* windowHandle);

		/// <summary>
		/// 初始化
		/// </summary>
		virtual void Init() override;

		/// <summary>
		/// 交换前后缓冲
		/// </summary>
		virtual void SwapBuffers() override;
	};
}