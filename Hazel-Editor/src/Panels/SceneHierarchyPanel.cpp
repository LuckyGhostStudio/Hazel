#include "SceneHierarchyPanel.h"

#include "Hazel/Scene/Components.h"

#include <imgui/imgui.h>

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
		ImGui::Begin("Hierarchy");

		//遍历场景所有实体，并调用each内的函数
		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);		//绘制实体结点
		});

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
}