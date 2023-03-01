#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{
	/// <summary>
	/// OpenGL������
	/// </summary>
	class OpenGLContext :public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;		//���ھ��

	public:
		/// <summary>
		/// OpenGL������
		/// </summary>
		/// <param name="windowHandle">���ھ��</param>
		OpenGLContext(GLFWwindow* windowHandle);

		/// <summary>
		/// ��ʼ��
		/// </summary>
		virtual void Init() override;

		/// <summary>
		/// ����ǰ�󻺳�
		/// </summary>
		virtual void SwapBuffers() override;
	};
}