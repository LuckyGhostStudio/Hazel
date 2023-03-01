#pragma once

#include "Hazel/Core/Layer.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	/// <summary>
	/// ImGui层
	/// </summary>
	class HAZEL_API ImGuiLayer :public Layer
	{
	private:
		float m_Time = 0.0f;	//当前帧时间
	public:
		ImGuiLayer();
		~ImGuiLayer();

		/// <summary>
		/// 将该层添加到层栈时调用
		/// </summary>
		virtual void OnAttach() override;

		/// <summary>
		/// 将该层从层栈移除时调用
		/// </summary>
		virtual void OnDetach() override;

		/// <summary>
		/// 开始窗口渲染
		/// </summary>
		void Begin();

		/// <summary>
		/// 结束窗口渲染
		/// </summary>
		void End();
	};
}