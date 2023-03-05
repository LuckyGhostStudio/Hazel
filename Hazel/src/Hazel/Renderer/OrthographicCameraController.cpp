#include "hzpch.h"
#include "OrthographicCameraController.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"

namespace Hazel
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera( -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	
	} 

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		HZ_PROFILE_FUNCTION();

		//相机移动
		if (Input::IsKeyPressed(HZ_KEY_A)) {		//左
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_D)) {	//右
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(HZ_KEY_W)) {		//上
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(HZ_KEY_S)) {	//下
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		}

		if (m_Rotation) {
			if (Input::IsKeyPressed(HZ_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * ts;
			}
			if (Input::IsKeyPressed(HZ_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * ts;
			}

			m_Camera.SetRotation(m_CameraRotation);		//设置相机旋转
		}

		m_Camera.SetPosition(m_CameraPosition);			//设置相机位置

		m_CameraTranslationSpeed = m_ZoomLevel;		//移动速度和缩放比例线性相关
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);	//事件调度器

		dispatcher.Dispatch<MouseScrolledEvent>(HZ_BIND_EVENT_FUNC(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(HZ_BIND_EVENT_FUNC(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		m_AspectRatio = width / height;	//设置宽高比
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);	//设置投影矩阵
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.5f;	//Y轴缩放比例减小
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);	//缩放>=0.25
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);	//设置投影矩阵

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		HZ_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());	//宽高比为 窗口 宽高比

		return false;
	}
}