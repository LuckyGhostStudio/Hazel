#pragma once
#include "hzpch.h"	//Ԥ����ͷ�ļ�

namespace Hazel
{
	/*
	* Events in Hazel are currently blocking,meaning when an event occurs
	* itimmediately gets dispatched and must be dealt with right then an there.
	* For the future, a better strategy might be to buffer events in an event
	* bus and process them during the "event" part of the update stage.
	*
	* Hazel�е��¼���ǰ��������״̬������ζ���¼�����ʱ
	* �����������ͣ�������������
	* δ�������õĲ��Կ��������¼��л����¼�
	* ���ߣ����ڸ��½׶εġ��¼������ִ������ǡ�
	*/

	/// <summary>
	/// �¼�����
	/// </summary>
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	//�����¼����ر� �ı��С �۽� ʧȥ���� �ƶ�
		AppTick, AppUpdate, AppRender,											//Ӧ���¼���ʱ�� ���� ��Ⱦ
		KeyPressed, KeyReleased, KeyTyped,										//�����¼������� ̧�� ���밴���ַ�
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled		//����¼������� ̧�� �ƶ� ���ֹ���
	};

	/// <summary>
	/// �¼�����
	/// </summary>
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),	// 1  App�¼�
		EventCategoryInput = BIT(1),		// 2  �����¼�
		EventCategoryKeyboard = BIT(2),		// 4  �����¼�
		EventCategoryMouse = BIT(3),		// 8  ����¼�
		EventCategoryMouseButton = BIT(4)	// 16 ��갴ť�¼�
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){ return EventType::##type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	/// <summary>
	/// �¼���
	/// </summary>
	class HAZEL_API Event
	{
		friend class EventDispatcher;
	public:
		/// <summary>
		/// �����¼�����
		/// </summary>
		/// <returns>�¼�����</returns>
		virtual EventType GetEventType() const = 0;

		/// <summary>
		/// �����¼���
		/// </summary>
		/// <returns>�¼���</returns>
		virtual const char* GetName() const = 0;

		/// <summary>
		/// �����¼�����־
		/// </summary>
		/// <returns>�¼�����־</returns>
		virtual int GetCategoryFlags() const = 0;

		/// <summary>
		/// �����¼������ַ���
		/// </summary>
		/// <returns>�¼���</returns>
		virtual std::string ToString() const { return GetName(); }

		/// <summary>
		/// ��ǰ�¼��Ƿ���Ŀ���¼�������
		/// </summary>
		/// <param name="category">Ŀ���¼�����</param>
		/// <returns>���</returns>
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;	//�¼�����־�� Ŀ���¼���� ��λ��
		}
	public:
		bool m_Handled = false;		//�Ƿ��Ѵ���
	};

	/// <summary>
	/// �¼�������
	/// </summary>
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;	//�¼����� bool func(T&)
	private:
		Event& m_Event;		//��ǰ���յ��¼�
	public:
		EventDispatcher(Event& event) :m_Event(event) {}

		/// <summary>
		/// �¼�����
		/// </summary>
		/// <typeparam name="T">����</typeparam>
		/// <param name="func">�¼�����</param>
		/// <returns>���Ƚ��</returns>
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType()) {		//���յ����¼����� == �¼���������
				m_Event.m_Handled = func(*(T*)&m_Event);			//ִ���¼����� func(Event& e)����m_Eventת��ΪT
				return true;
			}
			return false;
		}
	};

	/// <summary>
	/// �������������������¼�
	/// </summary>
	/// <param name="os">���������</param>
	/// <param name="e">�¼�</param>
	/// <returns>����¼�</returns>
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}