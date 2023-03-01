#include "hzpch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

#include "Platforms/OpenGL/OpenGLContext.h"

namespace Hazel
{
	static bool s_GLFWInitialized = false;	//GLFW是否已初始化

	/// <summary>
	/// GLFW错误回调函数
	/// </summary>
	/// <param name="error">错误类型</param>
	/// <param name="description">错误描述</param>
	static void GLFWErrorCallback(int error, const char* description)
	{
		HZ_CORE_ERROR("GLFW Error ({0}): {1}", error, description);		//输出错误日志
	}

	/// <summary>
	/// 创建窗口
	/// </summary>
	/// <param name="props">窗口属性</param>
	/// <returns>Windows平台窗口</returns>
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		HZ_PROFILE_FUNCTION();
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		HZ_PROFILE_FUNCTION();
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		HZ_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		HZ_CORE_INFO("Cteating window {0} ({1}, {2})", props.Title, props.Width, props.Height);	//输出日志信息：创建窗口

		if (!s_GLFWInitialized) {		//未初始化
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();	//初始化GLFW窗口
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");	//初始化失败 不能初始化GLFW
			glfwSetErrorCallback(GLFWErrorCallback);	//设置错误回调函数

			s_GLFWInitialized = true;
		}

		//创建GLFW窗口
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		m_Context = new OpenGLContext(m_Window);	//创建OpenGL上下文
		m_Context->Init();							//初始化

		glfwSetWindowUserPointer(m_Window, &m_Data);	//将数据m_Data传递给m_Window：userPtr指向m_Data
		SetVSync(true);									//垂直同步

		//----设置GLFW的回调函数----
		//窗口大小改变
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);	//通过userPtr指针获取window窗口的data数据
			
			//窗口更新后大小
			data.Width = width;
			data.Height = height;
			
			WindowResizeEvent event(width, height);	//创建窗口大小改变事件
			data.EventCallback(event);				//调用事件回调函数（回调函数已在Application中设置为OnEvent）<=> OnEvent(event)
		});

		//窗口关闭
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;		//窗口关闭事件
			data.EventCallback(event);
		});
		
		//键盘按键（按键代码 按键扫描码 行为 修改器位）
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:	//按键按下
				{
					KeyPressedEvent event(key, 0);	//按键按下事件
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:	//按键抬起
				{
					KeyReleasedEvent event(key);	//按键抬起事件
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:	//按键重复
				{
					KeyPressedEvent event(key, 1);	//按键按下事件
					data.EventCallback(event);
					break;
				}
			}
		});

		//键盘字符输入
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);	//按键输入字符事件
			data.EventCallback(event);
		});

		//鼠标
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:	//按键按下
				{
					MouseButtonPressedEvent event(button);	//鼠标按钮按下事件
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:	//按键抬起
				{
					MouseButtonReleasedEvent event(button);	//鼠标按钮抬起事件
					data.EventCallback(event);
					break;
				}
			}
		});

		//鼠标滚轮滚动
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);	//鼠标滚轮滚动事件
			data.EventCallback(event);
		});

		//鼠标移动
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);	//鼠标移动事件
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		HZ_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);	//销毁窗口
		glfwTerminate();
	}

	void WindowsWindow::OnUpdate()
	{
		HZ_PROFILE_FUNCTION();

		glfwPollEvents();			//轮询所有待处理的事件
		m_Context->SwapBuffers();	//交换前后缓冲区
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		HZ_PROFILE_FUNCTION();

		if (enabled) {
			glfwSwapInterval(1);	//交换间隔为1帧
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}