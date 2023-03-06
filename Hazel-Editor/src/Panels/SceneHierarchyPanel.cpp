#include "SceneHierarchyPanel.h"

#include "Hazel/Scene/Components.h"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

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

	/// <summary>
	/// ����Vector3�ؼ�
	/// </summary>
	/// <param name="label">��ǩ</param>
	/// <param name="values">ֵ</param>
	/// <param name="resetValue">����ֵ</param>
	/// <param name="columnWidth">ÿ�п��</param>
	static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGui::PushID(label.c_str());	//���ÿؼ���ǩ

		//��ǩ��
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);	//����0���п�
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());			//����3���п�
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });	//Var��ʽ

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;	//�и� = �����С + �߿�.y * 2
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };	//����ֵ��ť��С

		//X����UI
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));		//��ť��ɫ
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));	//�����ͣ�ڰ�ťʱ����ɫ
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));	//��ť������ɫ
		if (ImGui::Button("X", buttonSize)) {		//X��ť����
			values.x = resetValue;					//����x����
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();							//��ͬһ��
		ImGui::DragFloat("##X", &values.x, 0.1f);	//X������ ##����ʾ��ǩ �϶�����0.1
		ImGui::PopItemWidth();						//�Ƴ���һ���п�
		ImGui::SameLine();

		//Y����UI
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));		//��ť��ɫ
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));	//�����ͣ�ڰ�ťʱ����ɫ
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));	//��ť������ɫ
		if (ImGui::Button("Y", buttonSize)) {		//Y��ť����
			values.y = resetValue;					//����Y����
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();							//��ͬһ��
		ImGui::DragFloat("##Y", &values.y, 0.1f);	//Y������ ##����ʾ��ǩ �϶�����0.1
		ImGui::PopItemWidth();						//�Ƴ���һ���п�
		ImGui::SameLine();

		//Z����UI
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));		//��ť��ɫ
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));	//�����ͣ�ڰ�ťʱ����ɫ
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));	//��ť������ɫ
		if (ImGui::Button("Z", buttonSize)) {		//Z��ť����
			values.z = resetValue;					//����Z����
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();							//��ͬһ��
		ImGui::DragFloat("##Z", &values.z, 0.1f);	//Z������ ##����ʾ��ǩ �϶�����0.1
		ImGui::PopItemWidth();						//�Ƴ���һ���п�

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();	//�����ؼ���ǩ
	}
	
	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		//Tag���
		if (entity.HasComponent<TagComponent>()) {
			auto& tag = entity.GetComponent<TagComponent>().Tag;	//ʵ����

			char buffer[256];								//���������buffer
			memset(buffer, 0, sizeof(buffer));				//��buffer����
			strcpy_s(buffer, sizeof(buffer), tag.c_str());	//buffer = tag
			if (ImGui::InputText("Tag", buffer, sizeof(buffer))) {	//�����������������ݸı�ʱ
				tag = std::string(buffer);	//ʵ��tag��Ϊbuffer
			}
		}

		//Transform���
		if (entity.HasComponent<TransformComponent>()) {
			//Transform�����㣺Transform�����Ĺ�ϣֵ��Ϊ���id Ĭ�ϴ�
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {
				auto& transformComponent = entity.GetComponent<TransformComponent>();

				DrawVec3Control("Position", transformComponent.Position);	//λ��
				DrawVec3Control("Rotation", transformComponent.Rotation);	//��ת
				DrawVec3Control("Scale", transformComponent.Scale, 1.0f);	//����
				
				ImGui::TreePop();	//չ�����
			}
		}

		//Camera���
		if (entity.HasComponent<CameraComponent>()) {
			//Camera�����㣺Camera�����Ĺ�ϣֵ��Ϊ���id Ĭ�ϴ�
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera")) {
				auto& cameraComponent = entity.GetComponent<CameraComponent>();
				auto& camera = cameraComponent.Camera;

				ImGui::Checkbox("Primary", &cameraComponent.Primary);	//��������ÿ�

				const char* projectionTypeStrings[] = { "Perspective", "Orthographic"};	//ͶӰ���ͣ�͸�� ���� 
				const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];

				//������ ѡ��ͶӰ����
				if (ImGui::BeginCombo("Projection", currentProjectionTypeString)) {
					for (int i = 0; i < 2; i++) {
						bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];	//��ѡ�У���ǰͶӰ����==��i��ͶӰ����
						//��ѡ�������ı�ʱ��ͶӰ���� ��ѡ��
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
							currentProjectionTypeString = projectionTypeStrings[i];		//���õ�ǰͶӰ����
							camera.SetProjectionType((SceneCamera::ProjectionType)i);	//�������ͶӰ����
						}

						if (isSelected) {
							ImGui::SetItemDefaultFocus();	//Ĭ��ѡ����
						}
					}
					ImGui::EndCombo();
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {	//͸��ͶӰ
					float verticalFov = camera.GetVerticalFOV();	//��ֱ�Ž�
					if (ImGui::DragFloat("Vertical Fov", &verticalFov)) {
						camera.SetVerticalFOV(verticalFov);
					}
				}

				if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {	//����ͶӰ
					ImGui::Checkbox("Fixed Aspect Ratio", &cameraComponent.FixedAspectRatio);	//�̶���߱����ÿ�

					float size = camera.GetSize();		//�ߴ�
					if (ImGui::DragFloat("Size", &size)) {
						camera.SetSize(size);
					}
				}

				float nearClip = camera.GetNearClip();	//���ü�ƽ��
				if (ImGui::DragFloat("Near", &nearClip)) {
					camera.SetNearClip(nearClip);
				}
				
				float farClip = camera.GetFarClip();	//Զ�ü�ƽ��
				if (ImGui::DragFloat("Far", &farClip)) {
					camera.SetFarClip(farClip);
				}

				ImGui::TreePop();	//չ�����
			}
		}

		//SpriteRenderer���
		if (entity.HasComponent<SpriteRendererComponent>()) {
			//SpriteRenderer�����㣺SpriteRenderer�����Ĺ�ϣֵ��Ϊ���id Ĭ�ϴ�
			if (ImGui::TreeNodeEx((void*)typeid(SpriteRendererComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer")) {
				auto& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

				ImGui::ColorEdit4("Color", glm::value_ptr(spriteRenderer.Color));

				ImGui::TreePop();	//չ�����
			}
		}
	}
}