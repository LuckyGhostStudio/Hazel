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
		m_ProjectionType = ProjectionType::Perspective;		//透视投影

		m_FOV = verticalFOV;
		m_Near = nearClip;
		m_Far = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		m_ProjectionType = ProjectionType::Orthographic;	//正交投影

		m_Size = size;
		m_Near = nearClip;
		m_Far = farClip;

		RecalculateProjection();
	}
	
	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;					//宽高比
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_ProjectionType == ProjectionType::Perspective) {	//透视投影
			m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);	//设置透视投影矩阵
		}
		else {
			float orthLeft = -m_Size * m_AspectRatio * 0.5f;	//左边界
			float orthRight = m_Size * m_AspectRatio * 0.5f;	//右边界
			float orthBottom = -m_Size * 0.5f;					//下边界
			float orthTop = m_Size * 0.5f;						//上边界

			m_Projection = glm::ortho(orthLeft, orthRight, orthBottom, orthTop, m_Near, m_Far);	//设置正交投影矩阵
		}
	}
}