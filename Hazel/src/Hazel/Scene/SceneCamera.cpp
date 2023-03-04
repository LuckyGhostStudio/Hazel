#include "hzpch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}
	
	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalculateProjection();
	}
	
	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;					//��߱�
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float orthLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;	//��߽�
		float orthRight = m_OrthographicSize * m_AspectRatio * 0.5f;	//�ұ߽�
		float orthBottom = -m_OrthographicSize * 0.5f;					//�±߽�
		float orthTop = m_OrthographicSize * 0.5f;						//�ϱ߽�

		//����ͶӰ����
		m_Projection = glm::ortho(orthLeft, orthRight, orthBottom, orthTop, m_OrthographicNear, m_OrthographicFar);
	}
}