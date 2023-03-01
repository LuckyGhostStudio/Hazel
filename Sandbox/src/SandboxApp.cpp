#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox :public Hazel::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());	//ÃÌº” æ¿˝≤„µΩ≤„’ª
		PushLayer(new Sandbox2D());		//ÃÌº”2D‰÷»æ≤‚ ‘≤„
	}

	~Sandbox()
	{

	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}