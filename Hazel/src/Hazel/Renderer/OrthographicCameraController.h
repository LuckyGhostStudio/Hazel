#pragma once

#include "Hazel/Core/Timestep.h"
#include "Hazel/Renderer/OrthographicCamera.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel
{
	/// <summary>
	/// 正交相机边界
	/// </summary>
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	/// <summary>
	/// 正交相机控制器
	/// </summary>
	class OrthographicCameraController
	{
	private:
		float m_AspectRatio;				//宽高比（X/Y）
		float m_ZoomLevel = 1.0f;			//缩放比例（Y）
		OrthographicCameraBounds m_Bounds;	//正交相机边界
		OrthographicCamera m_Camera;		//正交相机
		 
		bool m_Rotation;				//是否可旋转

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };	//相机位置
		float m_CameraRotation = 0.0f;						//相机旋转（z轴）
		float m_CameraTranslationSpeed = 1.5f;				//相机移动速度
		float m_CameraRotationSpeed = 90.0f;				//相机旋转速度
	public:
		/// <summary>
		/// 正交相机控制器
		/// </summary>
		/// <param name="aspectRatio">宽高比（X/Y）</param>
		/// <param name="rotation">是否可旋转（false）</param>
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		/// <summary>
		/// 更新：每帧调用
		/// </summary>
		/// <param name="ts">帧间隔</param>
		void OnUpdate(Timestep ts);

		/// <summary>
		/// 事件回调函数：事件发生时调用
		/// </summary>
		/// <param name="e">事件</param>
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) 
		{ 
			m_ZoomLevel = level; 
			CalculateView();
		}

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
	private:
		/// <summary>
		/// 计算视图大小
		/// </summary>
		void CalculateView();

		/// <summary>
		/// 鼠标滚轮滚动
		/// </summary>
		/// <param name="e">鼠标滚轮滚动事件</param>
		/// <returns>事件处理结果</returns>
		bool OnMouseScrolled(MouseScrolledEvent& e);

		/// <summary>
		/// 窗口缩放
		/// </summary>
		/// <param name="e">窗口缩放事件</param>
		/// <returns>事件处理结果</returns>
		bool OnWindowResized(WindowResizeEvent& e);
	};
}