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
		m_CheckerboardTexture = Texture2D::Create("asserts/textures/Checkerboard.png");			//创建纹理

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { 
			FramebufferTextureFormat::RGBA8,		//颜色缓冲区0格式
			FramebufferTextureFormat::RED_INTEGER,	//颜色缓冲区1格式：作为id实现鼠标点击拾取
			FramebufferTextureFormat::Depth			//深度缓冲区格式
		};
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);	//创建帧缓冲区

		m_ActiveScene = CreateRef<Scene>();		//创建场景

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);	//创建编辑器相机
#if 0
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

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();	//添加脚本组件 并 绑定CameraController脚本
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
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//重置帧缓冲区大小
			//m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);				//重置相机大小
			
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);				//设置视口大小

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//重置视口大小
		}

		if (m_ViewportFocused) {	//视口被聚焦
			//m_CameraController.OnUpdate(ts);	//更新相机控制器
		}
			m_EditorCamera.OnUpdate(ts);	//更新编辑器相机

		Renderer2D::ResetStats();	//重置统计数据
		m_Framebuffer->Bind();		//绑定帧缓冲区
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });	//设置清屏颜色
		RenderCommand::Clear();										//清除

		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);	//编辑器更新场景

		auto [mx, my] = ImGui::GetMousePos();	//鼠标位置
		//计算鼠标相对于视口左上角的位置
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;

		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];	//视口大小
		my = viewportSize.y - my;	//翻转y坐标 左下角0,0（纹理坐标左下角为0,0）
		//鼠标相对于视口左上角的位置
		int mouseX = (int)mx;
		int mouseY = (int)my;
		//鼠标在视口内
		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y) {
			int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);	//读取1号颜色缓冲区像素
			HZ_CORE_WARN("pixelData:{0}", pixelData);
		}

		m_Framebuffer->Unbind();	//解除绑定帧缓冲区
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

		//菜单条
		if (ImGui::BeginMenuBar())
		{
			//菜单：File
			if (ImGui::BeginMenu("File"))
			{
				//创建新场景
				if (ImGui::MenuItem("New", "Ctrl+N")) {
					NewScene();
				}

				//打开文件：加载场景
				if (ImGui::MenuItem("Open...", "Ctrl+O")) {
					OpenScene();
				}

				//另存为：保存场景
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {
					SaveSceneAs();
				}

				//退出
				if (ImGui::MenuItem("Exit")) {
					Application::GetInstance().Close();	//退出程序
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

		//场景视口
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));	//设置Gui窗口样式：边界=0
		ImGui::Begin("Viewport");

		auto viewportOffset = ImGui::GetCursorPos();	//视口偏移量：视口左上角位置（相对于视口面板左上角的偏移量）
		
		m_ViewportFocused = ImGui::IsWindowFocused();	//当前窗口被聚焦
		m_ViewportHovered = ImGui::IsWindowHovered();	//鼠标悬停在当前窗口

		Application::GetInstance().GetImGuiLayer()->BlockEvents(/*!m_ViewportFocused && */!m_ViewportHovered);	//阻止ImGui事件

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();			//Gui面板大小
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };		//视口大小

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();	//颜色缓冲区0 ID
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));	//视口Image

		auto windowSize = ImGui::GetWindowSize();	//视口大小 包括tab bar
		ImVec2 minBound = ImGui::GetWindowPos();	//最小边界：视口面板左上角位置（相对于屏幕左上角）
		//最小边界为视口左上角
		minBound.x += viewportOffset.x;
		minBound.x += viewportOffset.x;

		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };	//最大边界：右下角
		
		m_ViewportBounds[0] = { minBound.x, minBound.y };	//视口最小边界：左上角
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };	//视口最大边界：右下角

		//Gizmo
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();	//被选中物体
		//选中物体存在 && Gizmo类型存在
		if (selectedEntity && m_GizmoType != -1) {
			ImGuizmo::SetOrthographic(false);	//透视投影
			ImGuizmo::SetDrawlist();			//设置绘制列表
			float windowWidth = (float)ImGui::GetWindowWidth();		//视口宽
			float windowHeight = (float)ImGui::GetWindowHeight();	//视口高
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);	//设置绘制区域

			//运行时相机
			//auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();				//主相机实体
			//const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;	//相机
			//const glm::mat4& cameraProjection = camera.GetProjection();					//投影矩阵
			//glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());	//视图矩阵

			//编辑器相机
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();	//投影矩阵
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();				//视图矩阵

			//被选中物体
			auto& transformComponent = selectedEntity.GetComponent<TransformComponent>();	//Transform组件
			glm::mat4 transform = transformComponent.GetTransform();

			bool span = Input::IsKeyPressed(Key::LeftControl);	//Ctrl刻度捕捉：操作时固定delta刻度
			float spanValue = 1.0f;	//平移缩放间隔：1m
			//旋转间隔值：5度
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE) {
				spanValue = 5.0f;
			}

			float spanValues[3] = { spanValue, spanValue, spanValue };	//xyz轴刻度捕捉值

			//绘制操作Gizmo：相机视图矩阵 相机投影矩阵 Gizmo类型 本地 选中物体transform 增量矩阵 刻度捕捉值
			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), 
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform), 
				nullptr, span ? spanValues : nullptr);
			
			//Gizmo被使用
			if (ImGuizmo::IsUsing()) {
				glm::vec3 position, rotation, scale;
				Math::DecomposeTransform(transform, position, rotation, scale);	//分解transform矩阵

				glm::vec3 deltaRotation =  glm::degrees(rotation) - transformComponent.Rotation;	//旋转增量

				transformComponent.Position = position;			//更新位置
				transformComponent.Rotation += deltaRotation;	//更新旋转：累加增量，避免万向节锁
				transformComponent.Scale = scale;				//更新缩放
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		//m_CameraController.OnEvent(event);	//调用相机事件函数
		m_EditorCamera.OnEvent(event);	//编辑器相机事件

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressedEvent>(HZ_BIND_EVENT_FUNC(EditorLayer::OnKeyPressed));	//调用按键按下事件
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		//快捷键：重复次数==0
		if (e.GetRepeatCount() > 0) {
			return false;
		}

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);	//Ctrl键按下
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);	//Shift键按下

		//菜单快捷键
		switch (e.GetKeyCode()) {
			case Key::N:
				if (control) {
					NewScene();		//创建新场景：Ctrl+N
				}
				break;
			case Key::O:
				if (control) {
					OpenScene();	//打开场景：Ctrl+O
				}
				break;
			case Key::S:
				if (control && shift) {
					SaveSceneAs();	//场景另存为：Ctrl+Shift+S
				}
				break;
		}

		//Gizmo快捷键
		switch (e.GetKeyCode())
		{
		case Key::G:
			m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;	//平移
			break;
		case Key::R:
			m_GizmoType = ImGuizmo::OPERATION::ROTATE;		//旋转
			break;
		case Key::S:
			m_GizmoType = ImGuizmo::OPERATION::SCALE;		//缩放
			break;
		}
	}

	void EditorLayer::NewScene()
	{
		m_ActiveScene = CreateRef<Scene>();			//创建新场景
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//重置视口大小
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);	//设置Hierarchy的场景
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileDialogs::OpenFile("Hazel Scene(*.hazel)\0*.hazel\0");	//打开文件对话框（文件类型名\0 文件类型）
					//路径不为空
		if (!filepath.empty()) {
			m_ActiveScene = CreateRef<Scene>();			//创建新场景
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);	//重置视口大小
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);	//设置Hierarchy的场景

			SceneSerializer serializer(m_ActiveScene);	//场景序列化器
			serializer.Deserialize(filepath);			//反序列化：加载文件场景到新场景
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileDialogs::SaveFile("Hazel Scene(*.hazel)\0*.hazel\0");	//保存文件对话框（文件类型名\0 文件类型）
					//路径不为空
		if (!filepath.empty()) {
			SceneSerializer serializer(m_ActiveScene);				//m_ActiveScene场景序列化器
			serializer.Serialize(filepath);	//序列化
		}
	}
}