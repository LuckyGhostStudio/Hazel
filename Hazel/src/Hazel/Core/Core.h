#pragma once

#include <memory>

#ifdef HZ_PLATFORM_WINDOWS	//windows平台
#if HZ_DYNAMIC_LINK	//动态链接
	#ifdef HZ_BUILD_DLL		//Hazel dll被构建时（在Hazel中）
		#define HAZEL_API __declspec(dllexport)		//导出Hazel dll
	#else	//在Sandbox中
		#define HAZEL_API __declspec(dllimport)		//导入Hazel dll
	#endif
#else 
	#define HAZEL_API
#endif
#else
	#error Hazel only supports Windows!
#endif

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif // HZ_DEBUG

#ifdef HZ_ENABLE_ASSERTS	//启用断言
	//断言：x为假 则显示ERROR日志信息 并中断调试
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	//断言：x为假 则显示ERROR日志信息 并中断调试
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else	//禁用断言
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)		//1左移x位

#define HZ_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)	//绑定事件函数 返回函数对象

namespace Hazel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;	//唯一指针
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;		//共享指针
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}