#pragma once

#include "Event.h"

namespace Hazel
{
	/// <summary>
	/// ���ڸı��С�¼�
	/// </summary>
	class HAZEL_API WindowResizeEvent :public Event
	{
	private:
		unsigned int m_Width;	//���������Ĵ��ڿ�
		unsigned int m_Height;	//���������Ĵ��ڸ�
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) :m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
	    EVENT_CLASS_CATEGORY(EventCategoryApplication)	//App�¼�
	};

	/// <summary>
	/// ���ڹر��¼�
	/// </summary>
	class HAZEL_API WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// Appʱ���¼�
	/// </summary>
	class HAZEL_API AppTickEvent :public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// App�����¼�
	/// </summary>
	class HAZEL_API AppUpdateEvent :public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// App��Ⱦ�¼�
	/// </summary>
	class HAZEL_API AppRenderEvent :public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}