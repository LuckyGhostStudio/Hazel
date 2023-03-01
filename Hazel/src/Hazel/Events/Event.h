#pragma once
#include "hzpch.h"	//预编译头文件

namespace Hazel
{
	/*
	* Events in Hazel are currently blocking,meaning when an event occurs
	* itimmediately gets dispatched and must be dealt with right then an there.
	* For the future, a better strategy might be to buffer events in an event
	* bus and process them during the "event" part of the update stage.
	*
	* Hazel中的事件当前处于阻塞状态，这意味着事件发生时
	* 它立即被发送，必须立即处理。
	* 未来，更好的策略可能是在事件中缓冲事件
	* 总线，并在更新阶段的“事件”部分处理它们。
	*/

	/// <summary>
	/// 事件类型
	/// </summary>
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	//窗口事件：关闭 改变大小 聚焦 失去焦点 移动
		AppTick, AppUpdate, AppRender,											//应用事件：时钟 更新 渲染
		KeyPressed, KeyReleased, KeyTyped,										//按键事件：按下 抬起 输入按键字符
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled		//鼠标事件：按下 抬起 移动 滚轮滚动
	};

	/// <summary>
	/// 事件种类
	/// </summary>
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),	// 1  App事件
		EventCategoryInput = BIT(1),		// 2  输入事件
		EventCategoryKeyboard = BIT(2),		// 4  键盘事件
		EventCategoryMouse = BIT(3),		// 8  鼠标事件
		EventCategoryMouseButton = BIT(4)	// 16 鼠标按钮事件
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){ return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/// <summary>
	/// 事件类
	/// </summary>
	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		/// <summary>
		/// 返回事件类型
		/// </summary>
		/// <returns>事件类型</returns>
		virtual EventType GetEventType() const = 0;

		/// <summary>
		/// 返回事件名
		/// </summary>
		/// <returns>事件名</returns>
		virtual const char* GetName() const = 0;

		/// <summary>
		/// 返回事件类别标志
		/// </summary>
		/// <returns>事件类别标志</returns>
		virtual int GetCategoryFlags() const = 0;

		/// <summary>
		/// 返回事件名：字符串
		/// </summary>
		/// <returns>事件名</returns>
		virtual std::string ToString() const { return GetName(); }

		/// <summary>
		/// 当前事件是否在目标事件分类中
		/// </summary>
		/// <param name="category">目标事件分类</param>
		/// <returns>结果</returns>
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;	//事件类别标志和 目标事件类别 按位与
		}
	public:
		bool m_Handled = false;		//是否已处理
	};

	/// <summary>
	/// 事件调度器
	/// </summary>
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;	//事件函数 bool func(T&)
	private:
		Event& m_Event;		//当前接收的事件
	public:
		EventDispatcher(Event& event) :m_Event(event) {}

		/// <summary>
		/// 事件调度
		/// </summary>
		/// <typeparam name="T">类型</typeparam>
		/// <param name="func">事件函数</param>
		/// <returns>调度结果</returns>
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType()) {		//接收到的事件类型 == 事件函数类型
				m_Event.m_Handled = func(*(T*)&m_Event);			//执行事件函数 func(Event& e)：将m_Event转换为T
				return true;
			}
			return false;
		}
	};

	/// <summary>
	/// 重载左移运算符：输出事件
	/// </summary>
	/// <param name="os">输出流对象</param>
	/// <param name="e">事件</param>
	/// <returns>输出事件</returns>
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}