#pragma once

#include "Event.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel
{
	/// <summary>
	/// 键盘按键事件：所有键盘事件的基类
	/// </summary>
	class KeyEvent :public Event
	{
	protected:
		KeyCode m_KeyCode;	//按键代码

		KeyEvent(const KeyCode keycode) :m_KeyCode(keycode) {}

	public:
		inline KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);	//键盘事件 | 输入事件
	};

	/// <summary>
	/// 按键按下事件
	/// </summary>
	class KeyPressedEvent :public KeyEvent
	{
	private:
		int m_RepeatCount;	//按键重复次数
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
	/// 按键抬起事件
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
	/// 按键输入字符事件
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