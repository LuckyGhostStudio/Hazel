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
		if (entity.HasComponent<TagComponent>()) {	//标签组件存在
			auto& tag = entity.GetComponent<TagComponent>().Tag;	//实体名

			char buffer[256];								//输入框内容buffer
			memset(buffer, 0, sizeof(buffer));				//将buffer置零
			strcpy_s(buffer, sizeof(buffer), tag.c_str());	//buffer = tag
			if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {	//创建输入框，输入框内容改变时
				tag = std::string(buffer);	//实体tag设为buffer
			}
		}
		if (entity.HasComponent<TransformComponent>()) {	//Transform组件存在
			//Transform组件结点：Transform组件类的哈希值作为结点id 默认打开
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
				auto& transform = entity.GetComponent<TransformComponent>().Transform;

				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);	//位置：拖动速度0.1
				
				ImGui::TreePop();	//展开结点
			}

		}
	}
}