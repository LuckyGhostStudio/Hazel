#pragma once

#include "Hazel/Core/Timestep.h"
#include "Hazel/Renderer/OrthographicCamera.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	/// <summary>
	/// ��������߽�
	/// </summary>
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	/// <summary>
	/// �������������
	/// </summary>
	class OrthographicCameraController
	{
	private:
		float m_AspectRatio;				//��߱ȣ�X/Y��
		float m_ZoomLevel = 1.0f;			//���ű�����Y��
		OrthographicCameraBounds m_Bounds;	//��������߽�
		OrthographicCamera m_Camera;		//�������
		 
		bool m_Rotation;				//�Ƿ����ת

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };	//���λ��
		float m_CameraRotation = 0.0f;						//�����ת��z�ᣩ
		float m_CameraTranslationSpeed = 1.5f;				//����ƶ��ٶ�
		float m_CameraRotationSpeed = 90.0f;				//�����ת�ٶ�
	public:
		/// <summary>
		/// �������������
		/// </summary>
		/// <param name="aspectRatio">��߱ȣ�X/Y��</param>
		/// <param name="rotation">�Ƿ����ת��false��</param>
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		/// <summary>
		/// ���£�ÿ֡����
		/// </summary>
		/// <param name="ts">֡���</param>
		void OnUpdate(Timestep ts);

		/// <summary>
		/// �¼��ص��������¼�����ʱ����
		/// </summary>
		/// <param name="e">�¼�</param>
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) 
		{ 
			m_ZoomLevel = level; 
			CalculateView();
		}

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
	private:
		/// <summary>
		/// ������ͼ��С
		/// </summary>
		void CalculateView();

		/// <summary>
		/// �����ֹ���
		/// </summary>
		/// <param name="e">�����ֹ����¼�</param>
		/// <returns>�¼�������</returns>
		bool OnMouseScrolled(MouseScrolledEvent& e);

		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="e">���������¼�</param>
		/// <returns>�¼�������</returns>
		bool OnWindowResized(WindowResizeEvent& e);
	};
}