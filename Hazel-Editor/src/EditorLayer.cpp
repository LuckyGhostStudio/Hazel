#include "EditorLayer.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
	EditorLayer::EditorLayer() :Layer("EditorLayer"), m_CameraController(1280.0f / 720.0f) {}

	void EditorLayer::OnAttach()
	{
		HZ_PROFILE_FUNCTION();

		m_CheckerboardTexture = Texture2D::Create("asserts/textures/Checkerboard.png");			//创建纹理

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);	//创建帧缓冲区
	}

	void EditorLayer::OnDetach()
	{
		HZ_PROFILE_FUNCTION();

	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		HZ_PROFILE_FUNCTION();

		{
			HZ_PROFILE_SCOPE("CameraController::OnUpdate");
			m_CameraController.OnUpdate(ts);	//更新相机控制器
		}

		Renderer2D::ResetStats();	//重置统计数据
		{
			HZ_PROFILE_SCOPE("Renderer Preparation");
			m_Framebuffer->Bind();	//绑定帧缓冲区
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });	//设置清屏颜色
			RenderCommand::Clear();										//清除
		}

		{
			static float rotation = 0.0f;
			rotation += 50 * ts;

			HZ_PROFILE_SCOPE("Renderer Draw");
			Renderer2D::BeginScene(m_CameraController.GetCamera());		//开始渲染场景

			Renderer2D::DrawRotateQuad({ 1.0f, 1.0f }, { 0.8f, 0.8f }, rotation, { 0.8f, 0.2f, 0.3f, 1.0f });	//绘制四边形
			Renderer2D::DrawRotateQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, 45.0f, m_CheckerboardTexture);	//绘制四边形
			Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });	//绘制四边形
			Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });	//绘制四边形
			Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);	//绘制四边形

			Renderer2D::EndScene();						//结束渲染场景

			Renderer2D::BeginScene(m_CameraController.GetCamera());		//开始渲染场景

			for (float y = -5.0f; y < 5.0f; y += 0.5f) {
				for (float x = -5.0f; x < 5.0f; x += 0.5f) {
					glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.6f };
					Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
				}
			}

			Renderer2D::EndScene();						//结束渲染场景
			m_Framebuffer->Unbind();	//解除绑定帧缓冲区
		}
	}

	void EditorLayer::OnImGuiRender()
	{
		HZ_PROFILE_FUNCTION();

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
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				//菜单项
				if (ImGui::MenuItem("Exit")) {	//退出
					Application::GetInstance().Close();	//退出程序
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quad: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));	//颜色编辑UI

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();	//颜色缓冲区ID
		ImGui::Image((void*)textureID, ImVec2{ 320.0f, 180.0f }, ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		m_CameraController.OnEvent(event);	//调用相机事件函数
	}
}