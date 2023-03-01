#pragma once

#include "Hazel/Core/Input.h"

namespace Hazel
{
	/// <summary>
	/// Windowsƽ̨������
	/// </summary>
	class WindowsInput :public Input
	{
	protected:
		/// <summary>
		/// �����Ƿ��£�����ʵ��
		/// </summary>
		/// <param name="keycode">��������</param>
		/// <returns>���</returns>
		virtual bool IsKeyPressedImpl(int keycode) override;

		/// <summary>
		/// ��갴ť�Ƿ��£�����ʵ��
		/// </summary>
		/// <param name="button">��ť����</param>
		/// <returns>���</returns>
		virtual bool IsMouseButtonPressedImpl(int button) override;

		/// <summary>
		/// �������λ�����꣺����ʵ��
		/// </summary>
		/// <returns>���λ��(x, y)</returns>
		virtual std::pair<float, float> GetMousePositionImpl() override;

		/// <summary>
		/// �������x���꣺����ʵ��
		/// </summary>
		/// <returns>���x����</returns>
		virtual float GetMouseXImpl() override;

		/// <summary>
		/// �������y���꣺����ʵ��
		/// </summary>
		/// <returns>���y����</returns>
		virtual float GetMouseYImpl() override;
	};
}