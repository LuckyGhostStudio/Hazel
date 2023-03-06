#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
	EditorLayer::EditorLayer() :Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f) {}

	void EditorLayer::OnAttach()
	{
		m_CheckerboardTexture = Texture2D::Create("asserts/textures/Checkerboard.png");			//创建纹理

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);	//创建帧缓冲区

		m_ActiveScene = CreateRef<Scene>();		//创建场景

		m_SquareEntity = m_ActiveScene->CreateEntity("Square");	//创建正方形实体
		m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));	//添加SpriteRenderer组件

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

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();	//添加脚本组件 并 绑定CameraController脚本

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
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//重置帧缓冲区大小
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);				//重置相机大小

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//重置视口大小
		}

		if (m_ViewportFocused) {	//视口被聚焦
			m_CameraController.OnUpdate(ts);	//更新相机控制器
		}

		Renderer2D::ResetStats();	//重置统计数据
		m_Framebuffer->Bind();		//绑定帧缓冲区
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });	//设置清屏颜色
		RenderCommand::Clear();										//清除

		//Renderer2D::BeginScene(m_CameraController.GetCamera());		//开始渲染场景
		m_ActiveScene->OnUpdate(ts);	//更新场景
		//Renderer2D::EndScene();			//结束渲染场景

		m_Framebuffer->Unbind();	//解除绑定帧缓冲区
	}

	void EditorLayer::OnImGuiRender()
	{
		static bool dockSpaceOpen = true;	//dockspace是否打开
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

		//菜单条
		if (ImGui::BeginMenuBar())
		{
			//菜单
			if (ImGui::BeginMenu("File"))
			{
				//菜单项
				if (ImGui::MenuItem("Exit")) {	//退出
					Application::GetInstance().Close();	//退出程序
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

		if (m_SquareEntity) {	//实体不为空
			ImGui::Separator();	//分隔符
			ImGui::Text("%s", m_SquareEntity.GetComponent<TagComponent>().Tag.c_str());			//正方形名字
			auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;	//正方形颜色
			ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));	//颜色编辑UI
			ImGui::Separator();
		}

		auto& camera = m_CameraEntity.GetComponent<CameraComponent>().Camera;
		float size = camera.GetSize();
		ImGui::Text("Main Camera");
		if (ImGui::DragFloat("Size", &size)) {
			camera.SetSize(size);
		}

		ImGui::End();

		//场景视口
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));	//设置Gui窗口样式：边界=0
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();	//当前窗口被聚焦
		m_ViewportHovered = ImGui::IsWindowHovered();	//鼠标悬停在当前窗口

		Application::GetInstance().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);	//阻止ImGui事件

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();			//Gui面板大小

		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };			//视口大小

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();	//颜色缓冲区ID
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);	//调用相机事件函数
	}
}