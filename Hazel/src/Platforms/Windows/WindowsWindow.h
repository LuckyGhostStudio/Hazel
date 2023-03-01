#pragma once

#include "Hazel/Core/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
	/// <summary>
	/// Windowsƽ̨����
	/// </summary>
	class WindowsWindow :public Window
	{
	private:
		GLFWwindow* m_Window;	//GLFW����

		GraphicsContext* m_Context;		//��Ⱦ������

		/// <summary>
		/// ��������
		/// </summary>
		struct WindowData
		{
			std::string Title;		//����
			unsigned int Width;		//��
			unsigned int Height;	//��
			bool VSync;				//�Ƿ�ֱͬ��

			EventCallbackFn EventCallback;	//�¼��ص�����
		};

		WindowData m_Data;	//��������
	private:
		/// <summary>
		/// ��ʼ������
		/// </summary>
		/// <param name="props">��������</param>
		virtual void Init(const WindowProps& props);

		/// <summary>
		/// �رմ���
		/// </summary>
		virtual void Shutdown();
	public:
		/// <summary>
		/// Windowsƽ̨����
		/// </summary>
		/// <param name="props">��������</param>
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		/// <summary>
		/// ���£�ÿ֡����
		/// </summary>
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		/// <summary>
		/// �����¼��ص�����
		/// </summary>
		/// <param name="callback">�ص�����</param>
		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		/// <summary>
		/// ���ô�ֱͬ��
		/// </summary>
		/// <param name="enabled">�Ƿ�����</param>
		void SetVSync(bool enabled) override;

		/// <summary>
		/// ����Ƿ�ֱͬ��
		/// </summary>
		/// <returns>���</returns>
		bool IsVSync() const override;

		/// <summary>
		/// ����ԭ������
		/// </summary>
		/// <returns>����ָ��</returns>
		inline virtual void* GetNativeWindow() const { return m_Window; }
	};
}