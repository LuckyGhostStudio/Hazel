#pragma once

#include "hzpch.h"

#include "Hazel/Core/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{
	/// <summary>
	/// 窗口属性
	/// </summary>
	struct WindowProps
	{
		std::string Title;		//标题
		unsigned int Width;		//宽
		unsigned int Height;	//高

		WindowProps(const std::string& title = "Hazel Engine", unsigned int width = 1280, unsigned int height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	/// <summary>
	/// 窗口类
	/// </summary>
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;	//事件回调函数 void func(Event&)

		virtual ~Window() {}

		/// <summary>
		/// 更新：每帧调用
		/// </summary>
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		/// <summary>
		/// 设置事件回调函数：从Application设置
		/// </summary>
		/// <param name="callback">回调函数</param>
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		/// <summary>
		/// 设置垂直同步
		/// </summary>
		/// <param name="enabled">是否启用</param>
		virtual void SetVSync(bool enabled) = 0;

		/// <summary>
		/// 检测是否垂直同步
		/// </summary>
		/// <returns>结果</returns>
		virtual bool IsVSync() const = 0;

		/// <summary>
		/// 返回原生窗口
		/// </summary>
		/// <returns>窗口指针</returns>
		virtual void* GetNativeWindow() const = 0;

		/// <summary>
		/// 创建窗口
		/// </summary>
		/// <param name="props">窗口属性</param>
		/// <returns>窗口</returns>
		static Window* Create(const WindowProps& props = WindowProps());
	};
}