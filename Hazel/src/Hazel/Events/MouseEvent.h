#pragma once

#include "Event.h"
#include "Hazel/Core/MouseButtonCodes.h"

namespace Hazel
{
	/// <summary>
	/// 鼠标移动事件
	/// </summary>
	class MouseMovedEvent :public Event
	{
	private:
		float m_MouseX;		//鼠标 x 坐标
		float m_MouseY;		//鼠标 y 坐标
	public:
		MouseMovedEvent(float x, float y) :m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)	//鼠标事件 | 输入事件
	};

	/// <summary>
	/// 鼠标滚轮滚动事件
	/// </summary>
	class MouseScrolledEvent :public Event
	{
	private:
		float m_XOffset;	//鼠标水平滚动偏移量
		float m_YOffset;	//鼠标竖直滚动偏移量
	public:
		MouseScrolledEvent(float xOffset, float yOffset) :m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)	//鼠标事件 | 输入事件
	};

	/// <summary>
	/// 鼠标按钮事件
	/// </summary>
	class MouseButtonEvent :public Event
	{
	protected:
		MouseCode m_Button;	//鼠标按钮

		MouseButtonEvent(const MouseCode button) :m_Button(button) {}
	public:
		inline MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)	//鼠标事件 | 输入事件
	};

	/// <summary>
	/// 鼠标按钮按下事件
	/// </summary>
	class MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button) :MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/// <summary>
	/// 鼠标按钮抬起事件
	/// </summary>
	class MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button) :MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}