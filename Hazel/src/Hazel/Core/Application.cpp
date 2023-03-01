#include "hzpch.h"	//Ԥ����ͷ�ļ�
#include "Application.h"

#include "Hazel/Core/Log.h"
#include "Hazel/Core/Input.h"

#include "Hazel/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)		//�󶨺��� ���غ�������

	Application* Application::s_Instance = nullptr;	//����

	Application::Application()
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(!s_Instance, "Application already exisit!");	//Application�Ѵ���
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());	//��������
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));		//���ûص�����

		Renderer::Init();	//��ʼ����Ⱦ��

		m_ImGuiLayer = new ImGuiLayer();		//����ImGui��
		PushOverlay(m_ImGuiLayer);				//���ImGuiLayer�����ǲ�
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();	//��ʼ����
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

		EventDispatcher dispatcher(e);	//�¼�������
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));	//���� ���ڹر��¼�
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));	//���� ���������¼�

		//��������±�����ջ
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);	//���ȡ�������¼�
			if (e.m_Handled) break;	//�¼��Ѵ��� ����
		}
	}
	
	void Application::Run()
	{
		HZ_PROFILE_FUNCTION();

		while (m_Running) {
			float time = (float)glfwGetTime();			//��ǰʱ��
			Timestep timestep = time - m_LastFrameTime;	//֡��� = ��ǰʱ�� - ��һ֡ʱ��
			m_LastFrameTime = time;						//������һ֡ʱ��

			if (!m_Minimized) {		//û����С��
				//���²�ջ�����в�
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}

				//ImGui��Ⱦ
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();		//��Ⱦÿ��Laye��ImGui
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();	//����Window
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;	//��������
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;		//������С��
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());	//���д������ź������

		return false;
	}
}