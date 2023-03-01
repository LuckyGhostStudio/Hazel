#pragma once

#include "Hazel.h"

/// <summary>
/// 2D��Ⱦ���Բ�
/// </summary>
class Sandbox2D :public Hazel::Layer
{
private:
	Hazel::OrthographicCameraController m_CameraController;		//���������

	//Temp
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;			//�����ζ�������
	Hazel::Ref<Hazel::Shader> m_FlatColorShader;		//��������ɫ��

	Hazel::Ref<Hazel::Texture2D> m_CheckerboardTexture;	//��������

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	/// <summary>
	/// ���ò���ӵ���ջʱ����
	/// </summary>
	virtual void OnAttach() override;

	/// <summary>
	/// ���ò�Ӳ�ջ�Ƴ�ʱ����
	/// </summary>
	virtual void OnDetach() override;

	/// <summary>
	/// �ò����ʱ���ã�ÿ֡����
	/// </summary>
	/// <param name="ts">֡���</param>
	virtual void OnUpdate(Hazel::Timestep ts) override;

	/// <summary>
	/// ��ȾImGui
	/// </summary>
	virtual void OnImGuiRender() override;

	/// <summary>
	/// �¼������������¼�
	/// </summary>
	/// <param name="event">�¼�</param>
	virtual void OnEvent(Hazel::Event& event) override;
};