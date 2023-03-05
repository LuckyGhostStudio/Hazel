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
		//Hierarchy���
		ImGui::Begin("Hierarchy");	
		//������������ʵ�壬������each�ڵĺ���
		m_Context->m_Registry.each([&](auto entityID)
		{
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);		//����ʵ����
		});
		ImGui::End();

		//TODO:ȡ��ѡ���ݲ�����
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered()) {	//�����ͣ�ڴ��� && ������ ������հ�λ�ã�
			m_SelectionContext = {};	//ȡ��ѡ�У��ÿ�ѡ������
		}

		//�������
		ImGui::Begin("Properties");
		if (m_SelectionContext) {	//��ѡ�е�ʵ�����
			DrawComponents(m_SelectionContext);		//�������
		}
		ImGui::End();
	}
	
	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;	//ʵ����
		
		//������־�����ƵĽڵ��Ƿ�ѡ�� ����ѡ�еı�־ ��0 | ������ͷʱ�򿪣�
		ImGuiTreeNodeFlags flags = (m_SelectionContext == entity ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());	//���ڵ㣺���id ����־ �������ʵ������
	
		if (ImGui::IsItemClicked()) {		//����㱻���
			m_SelectionContext = entity;	//entity��ѡ��
		}

		if (opened) {			//������Ѵ�
			ImGui::TreePop();	//չ�����
		}
	}
	
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>()) {	//��ǩ�������
			auto& tag = entity.GetComponent<TagComponent>().Tag;	//ʵ����

			char buffer[256];								//���������buffer
			memset(buffer, 0, sizeof(buffer));				//��buffer����
			strcpy_s(buffer, sizeof(buffer), tag.c_str());	//buffer = tag
			if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {	//�����������������ݸı�ʱ
				tag = std::string(buffer);	//ʵ��tag��Ϊbuffer
			}
		}
		if (entity.HasComponent<TransformComponent>()) {	//Transform�������
			//Transform�����㣺Transform�����Ĺ�ϣֵ��Ϊ���id Ĭ�ϴ�
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
				auto& transform = entity.GetComponent<TransformComponent>().Transform;

				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);	//λ�ã��϶��ٶ�0.1
				
				ImGui::TreePop();	//չ�����
			}

		}
	}
}