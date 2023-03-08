#pragma once

#include "Event.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel
{
	/// <summary>
	/// ���̰����¼������м����¼��Ļ���
	/// </summary>
	class KeyEvent :public Event
	{
	protected:
		KeyCode m_KeyCode;	//��������

		KeyEvent(const KeyCode keycode) :m_KeyCode(keycode) {}

	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);	//�����¼� | �����¼�
	};

	/// <summary>
	/// ���������¼�
	/// </summary>
	class KeyPressedEvent :public KeyEvent
	{
	private:
		int m_RepeatCount;	//�����ظ�����
	public:
		KeyPressedEvent(const KeyCode keycode, int repeatCount) :KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	/// <summary>
	/// ����̧���¼�
	/// </summary>
	class KeyReleasedEvent :public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	/// <summary>
	/// ���������ַ��¼�
	/// </summary>
	class KeyTypedEvent :public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode) :KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}