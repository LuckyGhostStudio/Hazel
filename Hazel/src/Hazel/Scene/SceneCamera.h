#pragma once

#include "Hazel/Renderer/Camera.h"

namespace Hazel
{
	/// <summary>
	/// 场景相机
	/// </summary>
	class SceneCamera :public Camera
	{
	public:
		/// <summary>
		/// 投影类型
		/// </summary>
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;

		float m_FOV = 45.0f;	//透视相机张角：垂直方向角度
		float m_Size = 10.0f;	//正交相机尺寸：垂直方向长度
		float m_Near = 0.01f;	//近裁剪平面
		float m_Far = 1000.0f;	//远裁剪平面

		float m_AspectRatio = 0.0f;			//宽高比

		/// <summary>
		/// 重新计算投影矩阵
		/// </summary>
		void RecalculateProjection();
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		/// <summary>
		/// 设置透视投影参数->计算投影矩阵
		/// </summary>
		/// <param name="verticalFOV">垂直张角</param>
		/// <param name="nearClip">近裁剪平面</param>
		/// <param name="farClip">远裁剪平面</param>
		void SetPerspective(float verticalFOV, float nearClip, float farClip);

		/// <summary>
		/// 设置正交投影参数->计算投影矩阵
		/// </summary>
		/// <param name="size">尺寸：垂直方向</param>
		/// <param name="nearClip">近裁剪平面</param>
		/// <param name="farClip">远裁剪平面</param>
		void SetOrthographic(float size, float nearClip, float farClip);

		/// <summary>
		/// 设置视口大小->计算投影矩阵
		/// </summary>
		/// <param name="width">宽</param>
		/// <param name="height">高</param>
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