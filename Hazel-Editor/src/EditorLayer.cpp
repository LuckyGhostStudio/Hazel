#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
	EditorLayer::EditorLayer() :Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f) {}

	void EditorLayer::OnAttach()
	{
		m_CheckerboardTexture = Texture2D::Create("asserts/textures/Checkerboard.png");			//��������

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);	//����֡������

		m_ActiveScene = CreateRef<Scene>();		//��������

		m_SquareEntity = m_ActiveScene->CreateEntity("Square");	//����������ʵ��
		m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));	//���SpriteRenderer���

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>();

		class CameraController :public ScriptableEntity
		{
		public:
			void OnCreate()
			{
				std::cout << "OnCreate" << std::endl;
			}

			void OnUpdate(Timestep ts)
			{
				auto& transform = GetComponent<TransformComponent>().Transform;
				float speed = 5.0f;

				if (Input::IsKeyPressed(KeyCode::W)) {
					transform[3][1] += speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::S)) {
					transform[3][1] -= speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::A)) {
					transform[3][0] -= speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::D)) {
					transform[3][0] += speed * ts;
				}
			}

			void OnDestroy()
			{
				
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();	//��ӽű���� �� ��CameraController�ű�

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OnDetach()
	{

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//����֡��������С
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);				//���������С

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//�����ӿڴ�С
		}

		if (m_ViewportFocused) {	//�ӿڱ��۽�
			m_CameraController.OnUpdate(ts);	//�������������
		}

		Renderer2D::ResetStats();	//����ͳ������
		m_Framebuffer->Bind();		//��֡������
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });	//����������ɫ
		RenderCommand::Clear();										//���

		//Renderer2D::BeginScene(m_CameraController.GetCamera());		//��ʼ��Ⱦ����
		m_ActiveScene->OnUpdate(ts);	//���³���
		//Renderer2D::EndScene();			//������Ⱦ����

		m_Framebuffer->Unbind();	//�����֡������
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockSpaceOpen = true;	//dockspace�Ƿ��
		static bool opt_fullscreen_persistant = true;
		static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
		bool opt_fullscreen = opt_fullscreen_persistant;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockSpaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Dockspace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
		}

		//�˵���
		if (ImGui::BeginMenuBar())
		{
			//�˵�
			if (ImGui::BeginMenu("File"))
			{
				//�˵���
				if (ImGui::MenuItem("Exit")) {	//�˳�
					Application::GetInstance().Close();	//�˳�����
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Settings");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		if (m_SquareEntity) {	//ʵ�岻Ϊ��
			ImGui::Separator();	//�ָ���
			ImGui::Text("%s", m_SquareEntity.GetComponent<TagComponent>().Tag.c_str());			//����������
			auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;	//��������ɫ
			ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));	//��ɫ�༭UI
			ImGui::Separator();
		}

		auto& camera = m_CameraEntity.GetComponent<CameraComponent>().Camera;
		float size = camera.GetSize();
		ImGui::Text("Main Camera");
		if (ImGui::DragFloat("Size", &size)) {
			camera.SetSize(size);
		}

		ImGui::End();

		//�����ӿ�
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));	//����Gui������ʽ���߽�=0
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();	//��ǰ���ڱ��۽�
		m_ViewportHovered = ImGui::IsWindowHovered();	//�����ͣ�ڵ�ǰ����

		Application::GetInstance().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);	//��ֹImGui�¼�

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();			//Gui����С

		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };			//�ӿڴ�С

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();	//��ɫ������ID
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);	//��������¼�����
	}
}