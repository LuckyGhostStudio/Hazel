#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Hazel/Scene/SceneSerializer.h"
#include "Hazel/Utils/PlatformUtils.h"

#include "ImGuizmo.h"

#include "Hazel/Math/Math.h"

namespace Hazel
{
	EditorLayer::EditorLayer() :Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f) {}

	void EditorLayer::OnAttach()
	{
		m_CheckerboardTexture = Texture2D::Create("asserts/textures/Checkerboard.png");			//��������

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { 
			FramebufferTextureFormat::RGBA8,		//��ɫ������0��ʽ
			FramebufferTextureFormat::RED_INTEGER,	//��ɫ������1��ʽ����Ϊidʵ�������ʰȡ
			FramebufferTextureFormat::Depth			//��Ȼ�������ʽ
		};
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);	//����֡������

		m_ActiveScene = CreateRef<Scene>();		//��������

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);	//�����༭�����
#if 0
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
				auto& position = GetComponent<TransformComponent>().Position;
				float speed = 5.0f;

				if (Input::IsKeyPressed(KeyCode::W)) {
					position.y += speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::S)) {
					position.y -= speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::A)) {
					position.x -= speed * ts;
				}
				if (Input::IsKeyPressed(KeyCode::D)) {
					position.x += speed * ts;
				}
			}

			void OnDestroy()
			{
				
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();	//��ӽű���� �� ��CameraController�ű�
#endif
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
			//m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);				//���������С
			
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);				//�����ӿڴ�С

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//�����ӿڴ�С
		}

		if (m_ViewportFocused) {	//�ӿڱ��۽�
			//m_CameraController.OnUpdate(ts);	//�������������
		}
			m_EditorCamera.OnUpdate(ts);	//���±༭�����

		Renderer2D::ResetStats();	//����ͳ������
		m_Framebuffer->Bind();		//��֡������
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });	//����������ɫ
		RenderCommand::Clear();										//���

		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);	//�༭�����³���

		auto [mx, my] = ImGui::GetMousePos();	//���λ��
		//�������������ӿ����Ͻǵ�λ��
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;

		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];	//�ӿڴ�С
		my = viewportSize.y - my;	//��תy���� ���½�0,0�������������½�Ϊ0,0��
		//���������ӿ����Ͻǵ�λ��
		int mouseX = (int)mx;
		int mouseY = (int)my;
		//������ӿ���
		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y) {
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);	//��ȡ1����ɫ����������
			HZ_CORE_WARN("pixelData:{0}", pixelData);
		}

		m_Framebuffer->Unbind();	//�����֡������
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

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

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		//�˵���
		if (ImGui::BeginMenuBar())
		{
			//�˵���File
			if (ImGui::BeginMenu("File"))
			{
				//�����³���
				if (ImGui::MenuItem("New", "Ctrl+N")) {
					NewScene();
				}

				//���ļ������س���
				if (ImGui::MenuItem("Open...", "Ctrl+O")) {
					OpenScene();
				}

				//���Ϊ�����泡��
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
					SaveSceneAs();
				}

				//�˳�
				if (ImGui::MenuItem("Exit")) {
					Application::GetInstance().Close();	//�˳�����
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Stats");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		//�����ӿ�
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));	//����Gui������ʽ���߽�=0
		ImGui::Begin("Viewport");

		auto viewportOffset = ImGui::GetCursorPos();	//�ӿ�ƫ�������ӿ����Ͻ�λ�ã�������ӿ�������Ͻǵ�ƫ������
		
		m_ViewportFocused = ImGui::IsWindowFocused();	//��ǰ���ڱ��۽�
		m_ViewportHovered = ImGui::IsWindowHovered();	//�����ͣ�ڵ�ǰ����

		Application::GetInstance().GetImGuiLayer()->BlockEvents(/*!m_ViewportFocused && */!m_ViewportHovered);	//��ֹImGui�¼�

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();			//Gui����С
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };		//�ӿڴ�С

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();	//��ɫ������0 ID
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));	//�ӿ�Image

		auto windowSize = ImGui::GetWindowSize();	//�ӿڴ�С ����tab bar
		ImVec2 minBound = ImGui::GetWindowPos();	//��С�߽磺�ӿ�������Ͻ�λ�ã��������Ļ���Ͻǣ�
		//��С�߽�Ϊ�ӿ����Ͻ�
		minBound.x += viewportOffset.x;
		minBound.x += viewportOffset.x;

		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };	//���߽磺���½�
		
		m_ViewportBounds[0] = { minBound.x, minBound.y };	//�ӿ���С�߽磺���Ͻ�
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };	//�ӿ����߽磺���½�

		//Gizmo
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();	//��ѡ������
		//ѡ��������� && Gizmo���ʹ���
		if (selectedEntity && m_GizmoType != -1) {
			ImGuizmo::SetOrthographic(false);	//͸��ͶӰ
			ImGuizmo::SetDrawlist();			//���û����б�
			float windowWidth = (float)ImGui::GetWindowWidth();		//�ӿڿ�
			float windowHeight = (float)ImGui::GetWindowHeight();	//�ӿڸ�
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);	//���û�������

			//����ʱ���
			//auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();				//�����ʵ��
			//const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;	//���
			//const glm::mat4& cameraProjection = camera.GetProjection();					//ͶӰ����
			//glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());	//��ͼ����

			//�༭�����
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();	//ͶӰ����
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();				//��ͼ����

			//��ѡ������
			auto& transformComponent = selectedEntity.GetComponent<TransformComponent>();	//Transform���
			glm::mat4 transform = transformComponent.GetTransform();

			bool span = Input::IsKeyPressed(Key::LeftControl);	//Ctrl�̶Ȳ�׽������ʱ�̶�delta�̶�
			float spanValue = 1.0f;	//ƽ�����ż����1m
			//��ת���ֵ��5��
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE) {
				spanValue = 5.0f;
			}

			float spanValues[3] = { spanValue, spanValue, spanValue };	//xyz��̶Ȳ�׽ֵ

			//���Ʋ���Gizmo�������ͼ���� ���ͶӰ���� Gizmo���� ���� ѡ������transform �������� �̶Ȳ�׽ֵ
			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), 
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), 
				nullptr, span ? spanValues : nullptr);
			
			//Gizmo��ʹ��
			if (ImGuizmo::IsUsing()) {
				glm::vec3 position, rotation, scale;
				Math::DecomposeTransform(transform, position, rotation, scale);	//�ֽ�transform����

				glm::vec3 deltaRotation =  glm::degrees(rotation) - transformComponent.Rotation;	//��ת����

				transformComponent.Position = position;			//����λ��
				transformComponent.Rotation += deltaRotation;	//������ת���ۼ������������������
				transformComponent.Scale = scale;				//��������
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		//m_CameraController.OnEvent(event);	//��������¼�����
		m_EditorCamera.OnEvent(event);	//�༭������¼�

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FUNC(EditorLayer::OnKeyPressed));	//���ð��������¼�
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		//��ݼ����ظ�����==0
		if (e.GetRepeatCount() > 0) {
			return false;
		}

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);	//Ctrl������
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);	//Shift������

		//�˵���ݼ�
		switch (e.GetKeyCode()) {
			case Key::N:
				if (control) {
					NewScene();		//�����³�����Ctrl+N
				}
				break;
			case Key::O:
				if (control) {
					OpenScene();	//�򿪳�����Ctrl+O
				}
				break;
			case Key::S:
				if (control && shift) {
					SaveSceneAs();	//�������Ϊ��Ctrl+Shift+S
				}
				break;
		}

		//Gizmo��ݼ�
		switch (e.GetKeyCode())
		{
		case Key::G:
			m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;	//ƽ��
			break;
		case Key::R:
			m_GizmoType = ImGuizmo::OPERATION::ROTATE;		//��ת
			break;
		case Key::S:
			m_GizmoType = ImGuizmo::OPERATION::SCALE;		//����
			break;
		}
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();			//�����³���
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//�����ӿڴ�С
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);	//����Hierarchy�ĳ���
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Hazel Scene(*.hazel)\0*.hazel\0");	//���ļ��Ի����ļ�������\0 �ļ����ͣ�
					//·����Ϊ��
		if (!filepath.empty()) {
			m_ActiveScene = CreateRef<Scene>();			//�����³���
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//�����ӿڴ�С
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);	//����Hierarchy�ĳ���

			SceneSerializer serializer(m_ActiveScene);	//�������л���
			serializer.Deserialize(filepath);			//�����л��������ļ��������³���
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Hazel Scene(*.hazel)\0*.hazel\0");	//�����ļ��Ի����ļ�������\0 �ļ����ͣ�
					//·����Ϊ��
		if (!filepath.empty()) {
			SceneSerializer serializer(m_ActiveScene);				//m_ActiveScene�������л���
			serializer.Serialize(filepath);	//���л�
		}
	}
}