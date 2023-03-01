#pragma once

#ifdef HZ_PLATFORM_WINDOWS

/// <summary>
/// 创建应用程序：在外部定义
/// </summary>
/// <returns>应用程序指针</returns>
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	auto app = Hazel::CreateApplication();	//创建应用程序
	app->Run();		//运行
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS
