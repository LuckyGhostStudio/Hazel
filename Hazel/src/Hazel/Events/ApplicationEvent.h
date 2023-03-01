#pragma once

#include "Event.h"

namespace Hazel
{
	/// <summary>
	/// 窗口改变大小事件
	/// </summary>
	class HAZEL_API WindowResizeEvent :public Event
	{
	private:
		unsigned int m_Width;	//被调整到的窗口宽
		unsigned int m_Height;	//被调整到的窗口高
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
	    EVENT_CLASS_CATEGORY(EventCategoryApplication)	//App事件
	};

	/// <summary>
	/// 窗口关闭事件
	/// </summary>
	class HAZEL_API WindowCloseEvent :public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// App时钟事件
	/// </summary>
	class HAZEL_API AppTickEvent :public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// App更新事件
	/// </summary>
	class HAZEL_API AppUpdateEvent :public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/// <summary>
	/// App渲染事件
	/// </summary>
	class HAZEL_API AppRenderEvent :public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}