#pragma once

namespace Hazel
{
	/// <summary>
	/// 时间步
	/// </summary>
	class Timestep
	{
	private:
		float m_Time;	//帧间隔时间（秒）
	public:
		Timestep(float time = 0.0f) :m_Time(time)
		{

		}

		/// <summary>
		/// 默认强转为float
		/// </summary>
		operator float() const { return m_Time; }

		/// <summary>
		/// 返回帧间隔时间（秒）
		/// </summary>
		/// <returns>秒</returns>
		float GetSeconds() const { return m_Time; }

		/// <summary>
		/// 返回帧间隔时间（毫秒）
		/// </summary>
		/// <returns>毫秒</returns>
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	};
}