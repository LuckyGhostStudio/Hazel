#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel
{
	/// <summary>
	/// 输入类
	/// </summary>
	class HAZEL_API Input
	{
	private:
		static Input* s_Instance;	//静态实例
	public:
		/// <summary>
		/// 按键是否按下
		/// </summary>
		/// <param name="keycode">按键代码</param>
		/// <returns>结果</returns>
		inline static bool IsKeyPressed(int keycode){ return s_Instance->IsKeyPressedImpl(keycode); }

		/// <summary>
		/// 鼠标按钮是否按下
		/// </summary>
		/// <param name="button">按钮代码</param>
		/// <returns>结果</returns>
		inline static bool IsMouseButtonPressed(int button){ return s_Instance->IsMouseButtonPressedImpl(button); }

		/// <summary>
		/// 返回鼠标位置坐标
		/// </summary>
		/// <returns>鼠标位置(x, y)</returns>
		inline static std::pair<float, float> GetMousePosition(){ return s_Instance->GetMousePositionImpl(); }

		/// <summary>
		/// 返回鼠标x坐标
		/// </summary>
		/// <returns>鼠标x坐标</returns>
		inline static float GetMouseX(){ return s_Instance->GetMouseXImpl(); }

		/// <summary>
		/// 返回鼠标y坐标
		/// </summary>
		/// <returns>鼠标y坐标</returns>
		inline static float GetMouseY(){ return s_Instance->GetMouseYImpl(); }
	protected:
		/// <summary>
		/// 按键是否按下：具体实现
		/// </summary>
		/// <param name="keycode">按键代码</param>
		/// <returns>结果</returns>
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		/// <summary>
		/// 鼠标按钮是否按下：具体实现
		/// </summary>
		/// <param name="button">按钮代码</param>
		/// <returns>结果</returns>
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		/// <summary>
		/// 返回鼠标位置坐标：具体实现
		/// </summary>
		/// <returns>鼠标位置(x, y)</returns>
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

		/// <summary>
		/// 返回鼠标x坐标：具体实现
		/// </summary>
		/// <returns>鼠标x坐标</returns>
		virtual float GetMouseXImpl() = 0;

		/// <summary>
		/// 返回鼠标y坐标：具体实现
		/// </summary>
		/// <returns>鼠标y坐标</returns>
		virtual float GetMouseYImpl() = 0;
	};
}