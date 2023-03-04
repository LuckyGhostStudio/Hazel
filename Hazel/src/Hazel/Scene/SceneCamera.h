#pragma once

#include "Hazel/Renderer/Camera.h"

namespace Hazel
{
	/// <summary>
	/// 场景相机
	/// </summary>
	class SceneCamera :public Camera
	{
	private:
		float m_OrthographicSize = 10.0f;	//正交相机尺寸：垂直方向长度
		float m_OrthographicNear = -1.0f;	//正交相机近裁剪平面
		float m_OrthographicFar = 1.0f;		//正交相机远裁剪平面

		float m_AspectRatio = 0.0f;			//宽高比

		/// <summary>
		/// 重新计算投影矩阵
		/// </summary>
		void RecalculateProjection();
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

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

		float GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection();}
	};
}