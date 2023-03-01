#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :m_WindowHandle(windowHandle)
	{
		HZ_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		HZ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);				//设置窗口上下文为当前线程主上下文

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);	//初始化GLAD
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Info");										//OpenGL信息
		HZ_CORE_INFO("    Vendor: {0}", (char*)glGetString(GL_VENDOR));		//出版商
		HZ_CORE_INFO("    Renderer: {0}", (char*)glGetString(GL_RENDERER));	//GPU类型
		HZ_CORE_INFO("    Version: {0}", (char*)glGetString(GL_VERSION));	//版本
	}

	void OpenGLContext::SwapBuffers()
	{
		HZ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);	//交换前后缓冲区
	}
}