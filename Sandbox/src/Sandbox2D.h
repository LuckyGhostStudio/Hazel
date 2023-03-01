#pragma once

#include "Hazel.h"

/// <summary>
/// 2D渲染测试层
/// </summary>
class Sandbox2D :public Hazel::Layer
{
private:
	Hazel::OrthographicCameraController m_CameraController;		//相机控制器

	//Temp
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;			//正方形顶点数组
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;		//正方形着色器

	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;	//棋盘纹理

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

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
	virtual void OnUpdate(Hazel::Timestep ts) override;

	/// <summary>
	/// 渲染ImGui
	/// </summary>
	virtual void OnImGuiRender() override;

	/// <summary>
	/// 事件函数：接收事件
	/// </summary>
	/// <param name="event">事件</param>
	virtual void OnEvent(Hazel::Event& event) override;
};