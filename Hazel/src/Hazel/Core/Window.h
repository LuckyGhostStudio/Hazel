#pragma once

#include "hzpch.h"

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	/// <summary>
	/// ��������
	/// </summary>
	struct WindowProps
	{
		std::string Title;		//����
		unsigned int Width;		//��
		unsigned int Height;	//��

		WindowProps(const std::string& title = "Hazel Engine", unsigned int width = 1280, unsigned int height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	/// <summary>
	/// ������
	/// </summary>
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;	//�¼��ص����� void func(Event&)

		virtual ~Window() {}

		/// <summary>
		/// ���£�ÿ֡����
		/// </summary>
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		/// <summary>
		/// �����¼��ص���������Application����
		/// </summary>
		/// <param name="callback">�ص�����</param>
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		/// <summary>
		/// ���ô�ֱͬ��
		/// </summary>
		/// <param name="enabled">�Ƿ�����</param>
		virtual void SetVSync(bool enabled) = 0;

		/// <summary>
		/// ����Ƿ�ֱͬ��
		/// </summary>
		/// <returns>���</returns>
		virtual bool IsVSync() const = 0;

		/// <summary>
		/// ����ԭ������
		/// </summary>
		/// <returns>����ָ��</returns>
		virtual void* GetNativeWindow() const = 0;

		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="props">��������</param>
		/// <returns>����</returns>
		static Window* Create(const WindowProps& props = WindowProps());
	};
}