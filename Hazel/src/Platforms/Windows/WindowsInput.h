#pragma once

#include "Hazel/Core/Input.h"

namespace Hazel
{
	/// <summary>
	/// Windows平台输入类
	/// </summary>
	class WindowsInput :public Input
	{
	protected:
		/// <summary>
		/// 按键是否按下：具体实现
		/// </summary>
		/// <param name="keycode">按键代码</param>
		/// <returns>结果</returns>
		virtual bool IsKeyPressedImpl(int keycode) override;

		/// <summary>
		/// 鼠标按钮是否按下：具体实现
		/// </summary>
		/// <param name="button">按钮代码</param>
		/// <returns>结果</returns>
		virtual bool IsMouseButtonPressedImpl(int button) override;

		/// <summary>
		/// 返回鼠标位置坐标：具体实现
		/// </summary>
		/// <returns>鼠标位置(x, y)</returns>
		virtual std::pair<float, float> GetMousePositionImpl() override;

		/// <summary>
		/// 返回鼠标x坐标：具体实现
		/// </summary>
		/// <returns>鼠标x坐标</returns>
		virtual float GetMouseXImpl() override;

		/// <summary>
		/// 返回鼠标y坐标：具体实现
		/// </summary>
		/// <returns>鼠标y坐标</returns>
		virtual float GetMouseYImpl() override;
	};
}