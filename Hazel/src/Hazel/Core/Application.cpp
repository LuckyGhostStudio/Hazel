#include "hzpch.h"	//预编译头文件
#include "Application.h"

#include "Hazel/Core/Log.h"
#include "Hazel/Core/Input.h"

#include "Hazel/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)		//绑定函数 返回函数对象

	Application* Application::s_Instance = nullptr;	//单例

	Application::Application()
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(!s_Instance, "Application already exisit!");	//Application已存在
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());	//创建窗口
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));		//设置回调函数

		Renderer::Init();	//初始化渲染器

		m_ImGuiLayer = new ImGuiLayer();		//创建ImGui层
		PushOverlay(m_ImGuiLayer);				//添加ImGuiLayer到覆盖层
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();	//初始化层
	}

	void Application::PushOverlay(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);	//事件调度器
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));	//调度 窗口关闭事件
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));	//调度 窗口缩放事件

		//从最顶层向下遍历层栈
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);	//层获取并处理事件
			if (e.m_Handled) break;	//事件已处理 跳出
		}
	}
	
	void Application::Run()
	{
		HZ_PROFILE_FUNCTION();

		while (m_Running) {
			float time = (float)glfwGetTime();			//当前时间
			Timestep timestep = time - m_LastFrameTime;	//帧间隔 = 当前时间 - 上一帧时间
			m_LastFrameTime = time;						//更新上一帧时间

			if (!m_Minimized) {		//没有最小化
				//更新层栈中所有层
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}

				//ImGui渲染
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();		//渲染每个Laye的ImGui
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();	//更新Window
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;	//结束运行
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;		//窗口最小化
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());	//进行窗口缩放后的设置

		return false;
	}
}