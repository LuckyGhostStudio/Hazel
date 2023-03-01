#pragma once

namespace Hazel
{
	/// <summary>
	/// ʱ�䲽
	/// </summary>
	class Timestep
	{
	private:
		float m_Time;	//֡���ʱ�䣨�룩
	public:
		Timestep(float time = 0.0f) :m_Time(time)
		{

		}

		/// <summary>
		/// Ĭ��ǿתΪfloat
		/// </summary>
		operator float() const { return m_Time; }

		/// <summary>
		/// ����֡���ʱ�䣨�룩
		/// </summary>
		/// <returns>��</returns>
		float GetSeconds() const { return m_Time; }

		/// <summary>
		/// ����֡���ʱ�䣨���룩
		/// </summary>
		/// <returns>����</returns>
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	};
}