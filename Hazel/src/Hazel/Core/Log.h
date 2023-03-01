#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hazel
{
	/// <summary>
	/// ��־
	/// </summary>
	class HAZEL_API Log
	{
	public:
		/// <summary>
		/// ��ʼ����־
		/// </summary>
		static void Init();

		/// <summary>
		/// �����ں���־
		/// </summary>
		/// <returns>�ں���־</returns>
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/// <summary>
		/// ���ؿͻ�����־
		/// </summary>
		/// <returns></returns>
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;		//�ں���־
		static std::shared_ptr<spdlog::logger> s_ClientLogger;		//�ͻ�����־
	};
}

//������־
#define HZ_CORE_TRACE(...) ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)	//��ʾ��־
#define HZ_CORE_INFO(...) ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)		//��Ϣ��־
#define HZ_CORE_WARN(...) ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)		//������־
#define HZ_CORE_ERROR(...) ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)	//������־
#define HZ_CORE_FATAL(...) ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)	//���ش�����־

//�ͻ�����־
#define HZ_TRACE(...) ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)	//��ʾ��־
#define HZ_INFO(...) ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)	//��Ϣ��־
#define HZ_WARN(...) ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)	//������־
#define HZ_ERROR(...) ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)	//������־
#define HZ_FATAL(...) ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)	//���ش�����־