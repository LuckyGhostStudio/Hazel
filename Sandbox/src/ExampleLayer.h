#pragma once

#include "Hazel.h"

/// <summary>
/// 示例层
/// </summary>
class ExampleLayer :public Hazel::Layer
{
private:
	Hazel::ShaderLibrary m_ShaderLibrary;				//着色器库
	Hazel::Ref<Hazel::Shader> m_Shader;					//三角形着色器
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;		//三角形顶点数组
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_ChernoLogoTexture;

	Hazel::OrthographicCameraController m_CameraController;		//相机控制器

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
public:
	ExampleLayer();

	virtual void OnUpdate(Hazel::Timestep ts) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Hazel::Event& event) override;
};