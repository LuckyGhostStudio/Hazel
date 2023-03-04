#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	/// <summary>
	/// 相机：运行时
	/// </summary>
	class Camera
	{
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);	//投影矩阵
	public:
		Camera() = default;
		Camera(const glm::mat4& projection) :m_Projection(projection)
		{

		}

		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return m_Projection; }
	};
}