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

		glfwMakeContextCurrent(m_WindowHandle);				//���ô���������Ϊ��ǰ�߳���������

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);	//��ʼ��GLAD
		HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

		HZ_CORE_INFO("OpenGL Info");										//OpenGL��Ϣ
		HZ_CORE_INFO("    Vendor: {0}", (char*)glGetString(GL_VENDOR));		//������
		HZ_CORE_INFO("    Renderer: {0}", (char*)glGetString(GL_RENDERER));	//GPU����
		HZ_CORE_INFO("    Version: {0}", (char*)glGetString(GL_VERSION));	//�汾
	}

	void OpenGLContext::SwapBuffers()
	{
		HZ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);	//����ǰ�󻺳���
	}
}