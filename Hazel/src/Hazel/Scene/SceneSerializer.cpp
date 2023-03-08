#include "hzpch.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Components.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace YAML 
{
	/// <summary>
	/// vec3转换
	/// </summary>
	template<>
	struct convert<glm::vec3>
	{
		/// <summary>
		/// 将vec3转换为YAML的节点
		/// </summary>
		/// <param name="rhs">vec3类型</param>
		/// <returns>结点</returns>
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		/// <summary>
		/// 将YAML结点类型转换为vec3
		/// </summary>
		/// <param name="node">结点</param>
		/// <param name="rhs">vec3</param>
		/// <returns>是否转换成功</returns>
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
	/// vec4转换
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
		out << YAML::Flow;	//流 [x,y,z]
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
	/// 序列化实体
	/// </summary>
	/// <param name="out">发射器</param>
	/// <param name="entity">实体</param>
	static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;	//开始实体Map
		out << YAML::Key << "Entity" << YAML::Value << "12837192831273"; // TODO: Entity ID goes here

		//Tag组件
		if (entity.HasComponent<TagComponent>()){
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;	//开始Tag组件Map
			
			auto& tag = entity.GetComponent<TagComponent>().Tag;	//Tag组件数据
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap;	//结束Tag组件Map
		}

		//Transform组件
		if (entity.HasComponent<TransformComponent>()) {
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap;	//开始Transform组件Map

			//Transform组件数据
			auto& transform = entity.GetComponent<TransformComponent>();

			out << YAML::Key << "Position" << YAML::Value << transform.Position;
			out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << transform.Scale;

			out << YAML::EndMap;	//结束Transform组件Map
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

		out << YAML::EndMap;	//结束实体Map
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;		//发射器
		out << YAML::BeginMap;	//开始场景Map
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";			//场景：场景名
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;	//实体：开始实体序列
		m_Scene->m_Registry.each([&](auto entityID)		//遍历场景注册表所有实体
		{
			Entity entity = { entityID, m_Scene.get() };
			if (!entity)
				return;

			SerializeEntity(out, entity);			//序列化实体
		});
		out << YAML::EndSeq;	//结束实体序列
		out << YAML::EndMap;	//结束场景Map

		std::ofstream fout(filepath);	//输出流
		fout << out.c_str();			//输出序列化结果到输出流文件
	}
	
	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		HZ_CORE_ASSERT(false, "Not implemented!");	//未实现
	}
	
	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);	//文件输入流
		std::stringstream strStream;
		strStream << stream.rdbuf();	//文件读入字符串

		YAML::Node data = YAML::Load(strStream.str());	//加载到YMAL结点
		//Scene节点不存在
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();	//场景名
		HZ_CORE_TRACE("Deserializing scene '{0}'", sceneName);

		YAML::Node entities = data["Entities"];	//实体序列结点

		if (entities) {	//实体存在
			for (auto entity : entities) {	//遍历结点下所有实体
				uint64_t uuid = entity["Entity"].as<uint64_t>(); //实体uid TODO

				std::string name;
				auto tagComponent = entity["TagComponent"];	//Tag组件
				if (tagComponent)
					name = tagComponent["Tag"].as<std::string>();	//实体名

				HZ_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

				Entity deserializedEntity = m_Scene->CreateEntity(name);	//创建实体

				auto transformComponent = entity["TransformComponent"];	//Transform组件
				//Transform组件存在
				if (transformComponent){
					auto& transform = deserializedEntity.GetComponent<TransformComponent>();	//获取Transform组件
					//设置组件数据
					transform.Position = transformComponent["Position"].as<glm::vec3>();
					transform.Rotation = transformComponent["Rotation"].as<glm::vec3>();
					transform.Scale = transformComponent["Scale"].as<glm::vec3>();
				}

				//Camera组件
				auto cameraComponent = entity["CameraComponent"];
				if (cameraComponent)
				{
					auto& cc = deserializedEntity.AddComponent<CameraComponent>();	//添加Camera组件

					auto& camera = cameraComponent["Camera"];
					//设置相机数据
					cc.Camera.SetProjectionType((SceneCamera::ProjectionType)camera["ProjectionType"].as<int>());
					
					cc.Camera.SetSize(camera["Size"].as<float>());
					cc.Camera.SetVerticalFOV(camera["FOV"].as<float>());
					cc.Camera.SetNearClip(camera["Near"].as<float>());
					cc.Camera.SetFarClip(camera["Far"].as<float>());

					cc.Primary = cameraComponent["Primary"].as<bool>();
					cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
				}

				//SpriteRenderer组件
				auto spriteRendererComponent = entity["SpriteRendererComponent"];
				if (spriteRendererComponent)
				{
					auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();	//添加SpriteRenderer组件
					src.Color = spriteRendererComponent["Color"].as<glm::vec4>();
				}
			}
		}

		return true;
	}
	
	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		HZ_CORE_ASSERT(false, "Not implemented!");	//未实现
		return false;
	}
}