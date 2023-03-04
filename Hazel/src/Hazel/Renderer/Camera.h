#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	/// <summary>
	/// ���������ʱ
	/// </summary>
	class Camera
	{
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);	//ͶӰ����
	public:
		Camera() = default;
		Camera(const glm::mat4& projection) :m_Projection(projection)
		{

		}

		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_Projection; }
	};
}