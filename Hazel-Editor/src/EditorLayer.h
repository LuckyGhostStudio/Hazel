#pragma once

#include "Hazel.h"

namespace Hazel
{
	/// <summary>
	/// 编辑器层
	/// </summary>
	class EditorLayer :public Layer
	{
	private:
		OrthographicCameraController m_CameraController;		//相机控制器

		//Temp
		Ref<VertexArray> m_SquareVA;		//正方形顶点数组
		Ref<Shader> m_FlatColorShader;		//正方形着色器
		Ref<Framebuffer> m_Framebuffer;		//帧缓冲区

		Ref<Texture2D> m_CheckerboardTexture;	//棋盘纹理

		Ref<Scene> m_ActiveScene;		//活动场景
		entt::entity m_SquareEntity;	//正方形实体

		bool m_ViewportFocused = false;				//视口被聚焦
		bool m_ViewportHovered = false;				//鼠标悬停在视口
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };	//视口大小

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		/// <summary>
		/// 将该层添加到层栈时调用
		/// </summary>
		virtual void OnAttach() override;

		/// <summary>
		/// 将该层从层栈移除时调用
		/// </summary>
		virtual void OnDetach() override;

		/// <summary>
		/// 该层更新时调用：每帧调用
		/// </summary>
		/// <param name="ts">帧间隔</param>
		virtual void OnUpdate(Timestep ts) override;

		/// <summary>
		/// 渲染ImGui
		/// </summary>
		virtual void OnImGuiRender() override;

		/// <summary>
		/// 事件函数：接收事件
		/// </summary>
		/// <param name="event">事件</param>
		virtual void OnEvent(Event& event) override;
	};
}