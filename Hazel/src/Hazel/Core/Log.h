#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hazel
{
	/// <summary>
	/// 日志
	/// </summary>
	class HAZEL_API Log
	{
	public:
		/// <summary>
		/// 初始化日志
		/// </summary>
		static void Init();

		/// <summary>
		/// 返回内核日志
		/// </summary>
		/// <returns>内核日志</returns>
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		/// <summary>
		/// 返回客户端日志
		/// </summary>
		/// <returns></returns>
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;		//内核日志
		static std::shared_ptr<spdlog::logger> s_ClientLogger;		//客户端日志
	};
}

//核心日志
#define HZ_CORE_TRACE(...) ::Hazel::Log::GetCoreLogger()->trace(__VA_ARGS__)	//提示日志
#define HZ_CORE_INFO(...) ::Hazel::Log::GetCoreLogger()->info(__VA_ARGS__)		//信息日志
#define HZ_CORE_WARN(...) ::Hazel::Log::GetCoreLogger()->warn(__VA_ARGS__)		//警告日志
#define HZ_CORE_ERROR(...) ::Hazel::Log::GetCoreLogger()->error(__VA_ARGS__)	//错误日志
#define HZ_CORE_FATAL(...) ::Hazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)	//严重错误日志

//客户端日志
#define HZ_TRACE(...) ::Hazel::Log::GetClientLogger()->trace(__VA_ARGS__)	//提示日志
#define HZ_INFO(...) ::Hazel::Log::GetClientLogger()->info(__VA_ARGS__)	//信息日志
#define HZ_WARN(...) ::Hazel::Log::GetClientLogger()->warn(__VA_ARGS__)	//警告日志
#define HZ_ERROR(...) ::Hazel::Log::GetClientLogger()->error(__VA_ARGS__)	//错误日志
#define HZ_FATAL(...) ::Hazel::Log::GetClientLogger()->fatal(__VA_ARGS__)	//严重错误日志