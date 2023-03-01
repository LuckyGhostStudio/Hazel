#pragma once

#include "Hazel/Core/Layer.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	/// <summary>
	/// ImGui��
	/// </summary>
	class HAZEL_API ImGuiLayer :public Layer
	{
	private:
		float m_Time = 0.0f;	//��ǰ֡ʱ��
	public:
		ImGuiLayer();
		~ImGuiLayer();

		/// <summary>
		/// ���ò���ӵ���ջʱ����
		/// </summary>
		virtual void OnAttach() override;

		/// <summary>
		/// ���ò�Ӳ�ջ�Ƴ�ʱ����
		/// </summary>
		virtual void OnDetach() override;

		/// <summary>
		/// ��ʼ������Ⱦ
		/// </summary>
		void Begin();

		/// <summary>
		/// ����������Ⱦ
		/// </summary>
		void End();
	};
}