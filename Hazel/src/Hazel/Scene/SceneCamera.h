#pragma once

#include "Hazel/Renderer/Camera.h"

namespace Hazel
{
	/// <summary>
	/// �������
	/// </summary>
	class SceneCamera :public Camera
	{
	public:
		/// <summary>
		/// ͶӰ����
		/// </summary>
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_FOV = 45.0f;	//͸������Žǣ���ֱ����Ƕ�
		float m_Size = 10.0f;	//��������ߴ磺��ֱ���򳤶�
		float m_Near = 0.01f;	//���ü�ƽ��
		float m_Far = 1000.0f;	//Զ�ü�ƽ��

		float m_AspectRatio = 0.0f;			//��߱�

		/// <summary>
		/// ���¼���ͶӰ����
		/// </summary>
		void RecalculateProjection();
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		/// <summary>
		/// ����͸��ͶӰ����->����ͶӰ����
		/// </summary>
		/// <param name="verticalFOV">��ֱ�Ž�</param>
		/// <param name="nearClip">���ü�ƽ��</param>
		/// <param name="farClip">Զ�ü�ƽ��</param>
		void SetPerspective(float verticalFOV, float nearClip, float farClip);

		/// <summary>
		/// ��������ͶӰ����->����ͶӰ����
		/// </summary>
		/// <param name="size">�ߴ磺��ֱ����</param>
		/// <param name="nearClip">���ü�ƽ��</param>
		/// <param name="farClip">Զ�ü�ƽ��</param>
		void SetOrthographic(float size, float nearClip, float farClip);

		/// <summary>
		/// �����ӿڴ�С->����ͶӰ����
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		void SetViewportSize(uint32_t width, uint32_t height);

		float GetVerticalFOV() const { return m_FOV; }
		void SetVerticalFOV(float verticalFOV) { m_FOV = verticalFOV; RecalculateProjection(); }

		float GetSize() const { return m_Size; }
		void SetSize(float size) { m_Size = size; RecalculateProjection();}

		float GetNearClip() const { return m_Near; }
		void SetNearClip(float nearClip) { m_Near = nearClip; RecalculateProjection(); }

		float GetFarClip() const { return m_Far; }
		void SetFarClip(float farClip) { m_Far = farClip; RecalculateProjection(); }

		ProjectionType GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(ProjectionType type) { m_ProjectionType = type; RecalculateProjection(); }
	};
}