#pragma once

#include "Hazel.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Hazel/Renderer/EditorCamera.h"

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
		EditorCamera m_EditorCamera;	//�༭�����

		Entity m_SquareEntity;		//������ʵ��
		Entity m_CameraEntity;		//���ʵ��

		bool m_ViewportFocused = false;				//�ӿڱ��۽�
		bool m_ViewportHovered = false;				//�����ͣ���ӿ�
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };	//�ӿڴ�С

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		int m_GizmoType = -1;	//Gizmo�������� -1�� 0ƽ�� 1��ת 2����

		SceneHierarchyPanel m_SceneHierarchyPanel;	//�������������
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

		/// <summary>
		/// �����³���
		/// </summary>
		void NewScene();

		/// <summary>
		/// �򿪳���
		/// </summary>
		void OpenScene();

		/// <summary>
		/// �������Ϊ
		/// </summary>
		void SaveSceneAs();
	private:
		/// <summary>
		/// ��������ʱ����
		/// </summary>
		/// <param name="e">���������¼�</param>
		/// <returns>������</returns>
		bool OnKeyPressed(KeyPressedEvent& e);
	};
}