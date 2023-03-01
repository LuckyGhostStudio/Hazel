#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel
{
	/// <summary>
	/// ������
	/// </summary>
	class HAZEL_API Input
	{
	private:
		static Input* s_Instance;	//��̬ʵ��
	public:
		/// <summary>
		/// �����Ƿ���
		/// </summary>
		/// <param name="keycode">��������</param>
		/// <returns>���</returns>
		inline static bool IsKeyPressed(int keycode){ return s_Instance->IsKeyPressedImpl(keycode); }

		/// <summary>
		/// ��갴ť�Ƿ���
		/// </summary>
		/// <param name="button">��ť����</param>
		/// <returns>���</returns>
		inline static bool IsMouseButtonPressed(int button){ return s_Instance->IsMouseButtonPressedImpl(button); }

		/// <summary>
		/// �������λ������
		/// </summary>
		/// <returns>���λ��(x, y)</returns>
		inline static std::pair<float, float> GetMousePosition(){ return s_Instance->GetMousePositionImpl(); }

		/// <summary>
		/// �������x����
		/// </summary>
		/// <returns>���x����</returns>
		inline static float GetMouseX(){ return s_Instance->GetMouseXImpl(); }

		/// <summary>
		/// �������y����
		/// </summary>
		/// <returns>���y����</returns>
		inline static float GetMouseY(){ return s_Instance->GetMouseYImpl(); }
	protected:
		/// <summary>
		/// �����Ƿ��£�����ʵ��
		/// </summary>
		/// <param name="keycode">��������</param>
		/// <returns>���</returns>
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		/// <summary>
		/// ��갴ť�Ƿ��£�����ʵ��
		/// </summary>
		/// <param name="button">��ť����</param>
		/// <returns>���</returns>
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		/// <summary>
		/// �������λ�����꣺����ʵ��
		/// </summary>
		/// <returns>���λ��(x, y)</returns>
		virtual std::pair<float, float> GetMousePositionImpl() = 0;

		/// <summary>
		/// �������x���꣺����ʵ��
		/// </summary>
		/// <returns>���x����</returns>
		virtual float GetMouseXImpl() = 0;

		/// <summary>
		/// �������y���꣺����ʵ��
		/// </summary>
		/// <returns>���y����</returns>
		virtual float GetMouseYImpl() = 0;
	};
}