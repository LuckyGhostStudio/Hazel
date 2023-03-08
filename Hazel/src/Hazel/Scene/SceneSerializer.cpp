#include "hzpch.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Components.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace YAML 
{
	/// <summary>
	/// vec3ת��
	/// </summary>
	template<>
	struct convert<glm::vec3>
	{
		/// <summary>
		/// ��vec3ת��ΪYAML�Ľڵ�
		/// </summary>
		/// <param name="rhs">vec3����</param>
		/// <returns>���</returns>
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		/// <summary>
		/// ��YAML�������ת��Ϊvec3
		/// </summary>
		/// <param name="node">���</param>
		/// <param name="rhs">vec3</param>
		/// <returns>�Ƿ�ת���ɹ�</returns>
		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	/// <summary>
	/// vec4ת��
	/// </summary>
	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Hazel
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;	//�� [x,y,z]
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene> scene) :m_Scene(scene)
	{

	}

	/// <summary>
	/// ���л�ʵ��
	/// </summary>
	/// <param name="out">������</param>
	/// <param name="entity">ʵ��</param>
	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;	//��ʼʵ��Map
		out << YAML::Key << "Entity" << YAML::Value << "12837192831273"; // TODO: Entity ID goes here

		//Tag���
		if (entity.HasComponent<TagComponent>()){
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;	//��ʼTag���Map
			
			auto& tag = entity.GetComponent<TagComponent>().Tag;	//Tag�������
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap;	//����Tag���Map
		}

		//Transform���
		if (entity.HasComponent<TransformComponent>()) {
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap;	//��ʼTransform���Map

			//Transform�������
			auto& transform = entity.GetComponent<TransformComponent>();

			out << YAML::Key << "Position" << YAML::Value << transform.Position;
			out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << transform.Scale;

			out << YAML::EndMap;	//����Transform���Map
		}

		if (entity.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; // CameraComponent

			auto& cameraComponent = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComponent.Camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; // Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "FOV" << YAML::Value << camera.GetVerticalFOV();
			out << YAML::Key << "Size" << YAML::Value << camera.GetSize();
			out << YAML::Key << "Near" << YAML::Value << camera.GetNearClip();
			out << YAML::Key << "Far" << YAML::Value << camera.GetFarClip();
			out << YAML::EndMap; // Camera

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

			out << YAML::EndMap; // CameraComponent
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

			out << YAML::EndMap; // SpriteRendererComponent
		}

		out << YAML::EndMap;	//����ʵ��Map
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;		//������
		out << YAML::BeginMap;	//��ʼ����Map
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";			//������������
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;	//ʵ�壺��ʼʵ������
		m_Scene->m_Registry.each([&](auto entityID)		//��������ע�������ʵ��
		{
			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);			//���л�ʵ��
		});
		out << YAML::EndSeq;	//����ʵ������
		out << YAML::EndMap;	//��������Map

		std::ofstream fout(filepath);	//�����
		fout << out.c_str();			//������л������������ļ�
	}
	
	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		HZ_CORE_ASSERT(false, "Not implemented!");	//δʵ��
	}
	
	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);	//�ļ�������
		std::stringstream strStream;
		strStream << stream.rdbuf();	//�ļ������ַ���

		YAML::Node data = YAML::Load(strStream.str());	//���ص�YMAL���
		//Scene�ڵ㲻����
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();	//������
		HZ_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		YAML::Node entities = data["Entities"];	//ʵ�����н��

		if (entities) {	//ʵ�����
			for (auto entity : entities) {	//�������������ʵ��
				uint64_t uuid = entity["Entity"].as<uint64_t>(); //ʵ��uid TODO

				std::string name;
				auto tagComponent = entity["TagComponent"];	//Tag���
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();	//ʵ����

				HZ_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntity(name);	//����ʵ��

				auto transformComponent = entity["TransformComponent"];	//Transform���
				//Transform�������
				if (transformComponent){
					auto& transform = deserializedEntity.GetComponent<TransformComponent>();	//��ȡTransform���
					//�����������
					transform.Position = transformComponent["Position"].as<glm::vec3>();
					transform.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					transform.Scale = transformComponent["Scale"].as<glm::vec3>();
				}

				//Camera���
				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.AddComponent<CameraComponent>();	//���Camera���

					auto& camera = cameraComponent["Camera"];
					//�����������
					cc.Camera.SetProjectionType((SceneCamera::ProjectionType)camera["ProjectionType"].as<int>());
					
					cc.Camera.SetSize(camera["Size"].as<float>());
					cc.Camera.SetVerticalFOV(camera["FOV"].as<float>());
					cc.Camera.SetNearClip(camera["Near"].as<float>());
					cc.Camera.SetFarClip(camera["Far"].as<float>());

					cc.Primary = cameraComponent["Primary"].as<bool>();
					cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
				}

				//SpriteRenderer���
				auto spriteRendererComponent = entity["SpriteRendererComponent"];
				if (spriteRendererComponent)
				{
					auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();	//���SpriteRenderer���
					src.Color = spriteRendererComponent["Color"].as<glm::vec4>();
				}
			}
		}

		return true;
	}
	
	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		HZ_CORE_ASSERT(false, "Not implemented!");	//δʵ��
		return false;
	}
}