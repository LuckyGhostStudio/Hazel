#pragma once

#include "Hazel/Core/Window.h"
#include "Hazel/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
	/// <summary>
	/// Windows平台窗口
	/// </summary>
	class WindowsWindow :public Window
	{
	private:
		GLFWwindow* m_Window;	//GLFW窗口

		GraphicsContext* m_Context;		//渲染上下文

		/// <summary>
		/// 窗口数据
		/// </summary>
		struct WindowData
		{
			std::string Title;		//标题
			unsigned int Width;		//宽
			unsigned int Height;	//高
			bool VSync;				//是否垂直同步

			EventCallbackFn EventCallback;	//事件回调函数
		};

		WindowData m_Data;	//窗口数据
	private:
		/// <summary>
		/// 初始化窗口
		/// </summary>
		/// <param name="props">窗口属性</param>
		virtual void Init(const WindowProps& props);

		/// <summary>
		/// 关闭窗口
		/// </summary>
		virtual void Shutdown();
	public:
		/// <summary>
		/// Windows平台窗口
		/// </summary>
		/// <param name="props">窗口属性</param>
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		/// <summary>
		/// 更新：每帧调用
		/// </summary>
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		/// <summary>
		/// 设置事件回调函数
		/// </summary>
		/// <param name="callback">回调函数</param>
		inline void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.EventCallback = callback;
		}

		/// <summary>
		/// 设置垂直同步
		/// </summary>
		/// <param name="enabled">是否启用</param>
		void SetVSync(bool enabled) override;

		/// <summary>
		/// 检测是否垂直同步
		/// </summary>
		/// <returns>结果</returns>
		bool IsVSync() const override;

		/// <summary>
		/// 返回原生窗口
		/// </summary>
		/// <returns>窗口指针</returns>
		inline virtual void* GetNativeWindow() const { return m_Window; }
	};
}