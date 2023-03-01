#pragma once

#include "Event.h"

namespace Hazel
{
	/// <summary>
	/// ����ƶ��¼�
	/// </summary>
	class HAZEL_API MouseMovedEvent :public Event
	{
	private:
		float m_MouseX;		//��� x ����
		float m_MouseY;		//��� y ����
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
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)	//����¼� | �����¼�
	};

	/// <summary>
	/// �����ֹ����¼�
	/// </summary>
	class HAZEL_API MouseScrolledEvent :public Event
	{
	private:
		float m_XOffset;	//���ˮƽ����ƫ����
		float m_YOffset;	//�����ֱ����ƫ����
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
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)	//����¼� | �����¼�
	};

	/// <summary>
	/// ��갴ť�¼�
	/// </summary>
	class HAZEL_API MouseButtonEvent :public Event
	{
	protected:
		int m_Button;	//��갴ť

		MouseButtonEvent(int button) :m_Button(button) {}
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)	//����¼� | �����¼�
	};

	/// <summary>
	/// ��갴ť�����¼�
	/// </summary>
	class HAZEL_API MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) :MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/// <summary>
	/// ��갴ţ̌���¼�
	/// </summary>
	class HAZEL_API MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) :MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}