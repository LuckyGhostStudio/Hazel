#include "hzpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}
	
	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Perspective;		//͸��ͶӰ

		m_FOV = verticalFOV;
		m_Near = nearClip;
		m_Far = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;	//����ͶӰ

		m_Size = size;
		m_Near = nearClip;
		m_Far = farClip;

		RecalculateProjection();
	}
	
	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;					//��߱�
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective) {	//͸��ͶӰ
			m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);	//����͸��ͶӰ����
		}
		else {
			float orthLeft = -m_Size * m_AspectRatio * 0.5f;	//��߽�
			float orthRight = m_Size * m_AspectRatio * 0.5f;	//�ұ߽�
			float orthBottom = -m_Size * 0.5f;					//�±߽�
			float orthTop = m_Size * 0.5f;						//�ϱ߽�

			m_Projection = glm::ortho(orthLeft, orthRight, orthBottom, orthTop, m_Near, m_Far);	//��������ͶӰ����
		}
	}
}