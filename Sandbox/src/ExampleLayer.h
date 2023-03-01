#pragma once

#include "Hazel.h"

/// <summary>
/// ʾ����
/// </summary>
class ExampleLayer :public Hazel::Layer
{
private:
	Hazel::ShaderLibrary m_ShaderLibrary;				//��ɫ����
	Hazel::Ref<Hazel::Shader> m_Shader;					//��������ɫ��
	Hazel::Ref<Hazel::VertexArray> m_VertexArray;		//�����ζ�������
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;

	Hazel::Ref<Hazel::Texture2D> m_Texture, m_ChernoLogoTexture;

	Hazel::OrthographicCameraController m_CameraController;		//���������

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
public:
	ExampleLayer();

	virtual void OnUpdate(Hazel::Timestep ts) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Hazel::Event& event) override;
};