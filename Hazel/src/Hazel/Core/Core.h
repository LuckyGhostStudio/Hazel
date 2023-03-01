#pragma once

#include <memory>

#ifdef HZ_PLATFORM_WINDOWS	//windowsƽ̨
#if HZ_DYNAMIC_LINK	//��̬����
	#ifdef HZ_BUILD_DLL		//Hazel dll������ʱ����Hazel�У�
		#define HAZEL_API __declspec(dllexport)		//����Hazel dll
	#else	//��Sandbox��
		#define HAZEL_API __declspec(dllimport)		//����Hazel dll
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

#ifdef HZ_ENABLE_ASSERTS	//���ö���
	//���ԣ�xΪ�� ����ʾERROR��־��Ϣ ���жϵ���
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	//���ԣ�xΪ�� ����ʾERROR��־��Ϣ ���жϵ���
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else	//���ö���
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)		//1����xλ

#define HZ_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)	//���¼����� ���غ�������

namespace Hazel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;	//Ψһָ��
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;		//����ָ��
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}