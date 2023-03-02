#pragma once

#include "Hazel.h"

namespace Hazel
{
	/// <summary>
	/// �༭����
	/// </summary>
	class EditorLayer :public Layer
	{
	private:
		OrthographicCameraController m_CameraController;		//���������

		//Temp
		Ref<VertexArray> m_SquareVA;		//�����ζ�������
		Ref<Shader> m_FlatColorShader;		//��������ɫ��
		Ref<Framebuffer> m_Framebuffer;		//֡������

		Ref<Texture2D> m_CheckerboardTexture;	//��������

		Ref<Scene> m_ActiveScene;		//�����
		entt::entity m_SquareEntity;	//������ʵ��

		bool m_ViewportFocused = false;				//�ӿڱ��۽�
		bool m_ViewportHovered = false;				//�����ͣ���ӿ�
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };	//�ӿڴ�С

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

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
		virtual void OnUpdate(Timestep ts) override;

		/// <summary>
		/// ��ȾImGui
		/// </summary>
		virtual void OnImGuiRender() override;

		/// <summary>
		/// �¼������������¼�
		/// </summary>
		/// <param name="event">�¼�</param>
		virtual void OnEvent(Event& event) override;
	};
}