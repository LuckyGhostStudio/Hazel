#pragma once

namespace Hazel
{
	/// <summary>
	/// ��Ⱦ������
	/// </summary>
	class GraphicsContext
	{
	public:
		/// <summary>
		/// ��ʼ��
		/// </summary>
		virtual void Init() = 0;

		/// <summary>
		/// ����ǰ�󻺳�
		/// </summary>
		virtual void SwapBuffers() = 0;
	};
}