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
		m_AspectRatio = (float)width / (float)height;					//宽高比
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float orthLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;	//左边界
		float orthRight = m_OrthographicSize * m_AspectRatio * 0.5f;	//右边界
		float orthBottom = -m_OrthographicSize * 0.5f;					//下边界
		float orthTop = m_OrthographicSize * 0.5f;						//上边界

		//正交投影矩阵
		m_Projection = glm::ortho(orthLeft, orthRight, orthBottom, orthTop, m_OrthographicNear, m_OrthographicFar);
	}
}