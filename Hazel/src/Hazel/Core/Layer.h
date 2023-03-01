#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	/// <summary>
	/// ��
	/// </summary>
	class HAZEL_API Layer
	{
	protected:
		std::string m_DebugName;	//Layer��Debugģʽ�е�����
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		/// <summary>
		/// ���ò���ӵ���ջʱ����
		/// </summary>
		virtual void OnAttach() {}
		
		/// <summary>
		/// ���ò�Ӳ�ջ�Ƴ�ʱ����
		/// </summary>
		virtual void OnDetach() {}
		
		/// <summary>
		/// �ò����ʱ���ã�ÿ֡����
		/// </summary>
		/// <param name="ts">֡���</param>
		virtual void OnUpdate(Timestep ts) {}

		/// <summary>
		/// ��ȾImGui
		/// </summary>
		virtual void OnImGuiRender() {}

		/// <summary>
		/// �¼������������¼�
		/// </summary>
		/// <param name="event">�¼�</param>
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	};
}