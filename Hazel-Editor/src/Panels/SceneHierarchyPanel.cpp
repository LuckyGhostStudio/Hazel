#include "SceneHierarchyPanel.h"

#include "Hazel/Scene/Components.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}
	
	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}
	
	void SceneHierarchyPanel::OnImGuiRender()
	{
		//Hierarchy面板
		ImGui::Begin("Hierarchy");	
		//遍历场景所有实体，并调用each内的函数
		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);		//绘制实体结点
		});
		ImGui::End();

		//TODO:取消选中暂不可用
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {	//鼠标悬停在窗口 && 点击鼠标 （点击空白位置）
			m_SelectionContext = {};	//取消选中：置空选中物体
		}

		//属性面板
		ImGui::Begin("Properties");
		if (m_SelectionContext) {	//被选中的实体存在
			DrawComponents(m_SelectionContext);		//绘制组件
		}
		ImGui::End();
	}
	
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;	//实体名
		
		//树结点标志（绘制的节点是否被选中 ？被选中的标志 ：0 | 单击箭头时打开）
		ImGuiTreeNodeFlags flags = (m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());	//树节点：结点id 结点标志 结点名（实体名）
	
		if (ImGui::IsItemClicked()) {		//树结点被点击
			m_SelectionContext = entity;	//entity被选中
		}

		if (opened) {			//树结点已打开
			ImGui::TreePop();	//展开结点
		}
	}
	
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		//Tag组件
		if (entity.HasComponent<TagComponent>()) {
			auto& tag = entity.GetComponent<TagComponent>().Tag;	//实体名

			char buffer[256];								//输入框内容buffer
			memset(buffer, 0, sizeof(buffer));				//将buffer置零
			strcpy_s(buffer, sizeof(buffer), tag.c_str());	//buffer = tag
			if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {	//创建输入框，输入框内容改变时
				tag = std::string(buffer);	//实体tag设为buffer
			}
		}

		//Transform组件
		if (entity.HasComponent<TransformComponent>()) {
			//Transform组件结点：Transform组件类的哈希值作为结点id 默认打开
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
				auto& transform = entity.GetComponent<TransformComponent>().Transform;

				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);	//位置：拖动速度0.1
				
				ImGui::TreePop();	//展开结点
			}
		}

		//Camera组件
		if (entity.HasComponent<CameraComponent>()) {
			//Camera组件结点：Camera组件类的哈希值作为结点id 默认打开
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")) {
				auto& cameraComponent = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComponent.Camera;

				ImGui::Checkbox("Primary", &cameraComponent.Primary);	//主相机设置框

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic"};	//投影类型：透视 正交 
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];

				//下拉框 选择投影类型
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
					for (int i = 0; i < 2; i++) {
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];	//被选中：当前投影类型==第i个投影类型
						//可选择项，该项改变时：投影类型 已选中
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
							currentProjectionTypeString = projectionTypeStrings[i];		//设置当前投影类型
							camera.SetProjectionType((SceneCamera::ProjectionType)i);	//设置相机投影类型
						}

						if (isSelected) {
							ImGui::SetItemDefaultFocus();	//默认选中项
						}
					}
					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {	//透视投影
					float verticalFov = camera.GetVerticalFOV();	//垂直张角
					if (ImGui::DragFloat("Vertical Fov", &verticalFov)) {
						camera.SetVerticalFOV(verticalFov);
					}
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {	//正交投影
					ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.FixedAspectRatio);	//固定宽高比设置框

					float size = camera.GetSize();		//尺寸
					if (ImGui::DragFloat("Size", &size)) {
						camera.SetSize(size);
					}
				}

				float nearClip = camera.GetNearClip();	//近裁剪平面
				if (ImGui::DragFloat("Near", &nearClip)) {
					camera.SetNearClip(nearClip);
				}
				
				float farClip = camera.GetFarClip();	//远裁剪平面
				if (ImGui::DragFloat("Far", &farClip)) {
					camera.SetFarClip(farClip);
				}

				ImGui::TreePop();	//展开结点
			}
		}
	}
}