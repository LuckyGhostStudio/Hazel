#pragma once

#include "Hazel/Renderer/Camera.h"

namespace Hazel
{
	/// <summary>
	/// �������
	/// </summary>
	class SceneCamera :public Camera
	{
	private:
		float m_OrthographicSize = 10.0f;	//��������ߴ磺��ֱ���򳤶�
		float m_OrthographicNear = -1.0f;	//����������ü�ƽ��
		float m_OrthographicFar = 1.0f;		//�������Զ�ü�ƽ��

		float m_AspectRatio = 0.0f;			//��߱�

		/// <summary>
		/// ���¼���ͶӰ����
		/// </summary>
		void RecalculateProjection();
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

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

		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection();}
	};
}