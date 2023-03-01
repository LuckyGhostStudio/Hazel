#include "hzpch.h"
#include "WindowsInput.h"

#include "Hazel/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
	Input* Input::s_Instance = new WindowsInput();		//��̬ʵ��

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());	//GLFW����
		auto state = glfwGetKey(window, keycode);				//��ȡkeycode����״̬
		return state == GLFW_PRESS || state == GLFW_REPEAT;		//��������||�����ظ�
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());	//GLFW����
		auto state = glfwGetMouseButton(window, button);		//��ȡbutton״̬
		return state == GLFW_PRESS;								//��������
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());	//GLFW����

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);		//��ȡ��� x y ����

		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		return GetMousePositionImpl().first;	//x����
	}
	float WindowsInput::GetMouseYImpl()
	{
		return GetMousePositionImpl().second;	//y����
	}
}