#pragma once

#ifdef HZ_PLATFORM_WINDOWS

/// <summary>
/// ����Ӧ�ó������ⲿ����
/// </summary>
/// <returns>Ӧ�ó���ָ��</returns>
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	auto app = Hazel::CreateApplication();	//����Ӧ�ó���
	app->Run();		//����
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS
