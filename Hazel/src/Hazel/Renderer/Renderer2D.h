#pragma once

#include "OrthographicCamera.h"
#include "Texture.h"
#include "SubTexture2D.h"
#include "Hazel/Renderer/Camera.h"
#include "Hazel/Renderer/EditorCamera.h"
#include "Hazel/Scene/Components.h"

namespace Hazel
{
	class Renderer2D
	{
	public:
		/// <summary>
		/// ��ʼ����Ⱦ��
		/// </summary>
		static void Init();

		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);

		static void BeginScene(const EditorCamera& camera);
		
		/// <summary>
		/// ��ʼ��Ⱦ���������ó�������
		/// </summary>
		/// <param name="camera">���</param>
		static void BeginScene(const OrthographicCamera& camera);


		/// <summary>
		/// ������Ⱦ����
		/// </summary>
		static void EndScene();

		/// <summary>
		/// ˢ��
		/// </summary>
		static void Flush();

		/// <summary>
		/// ���Ƴ�����
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="color">��ɫ</param>
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		/// <summary>
		/// ���Ƴ�����
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="color">��ɫ</param>
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		/// <summary>
		/// ���Ƴ�����
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="texture">����</param>
		/// <param name="tilingFactor">�����ظ�����</param>
		/// <param name="tintColor">��ɫ</param>
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// ���Ƴ�����
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="texture">����</param>
		/// <param name="tintColor">��ɫ</param>
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		
		/// <summary>
		/// ���Ƴ�����
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="texture">������</param>
		/// <param name="tilingFactor">�����ظ�����</param>
		/// <param name="tintColor">��ɫ</param>
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// ���Ƴ�����
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="texture">������</param>
		/// <param name="tintColor">��ɫ</param>
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);

		/// <summary>
		/// ������ת������
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="rotation">��ת</param>
		/// <param name="color">��ɫ</param>
		static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		/// <summary>
		/// ������ת������
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="rotation">��ת</param>
		/// <param name="color">��ɫ</param>
		static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

		/// <summary>
		/// ������ת������
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="rotation">��ת</param>
		/// <param name="texture">����</param>
		/// <param name="tilingFactor">�����ظ�����</param>
		static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// ������ת������
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="rotation">��ת</param>
		/// <param name="texture">����</param>
		/// <param name="tilingFactor">�����ظ�����</param>
		static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		/// <summary>
		/// ������ת������
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="rotation">��ת</param>
		/// <param name="texture">������</param>
		/// <param name="tilingFactor">�����ظ�����</param>
		static void DrawRotateQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// <summary>
		/// ������ת������
		/// </summary>
		/// <param name="position">λ��</param>
		/// <param name="size">��С</param>
		/// <param name="rotation">��ת</param>
		/// <param name="texture">������</param>
		/// <param name="tilingFactor">�����ظ�����</param>
		static void DrawRotateQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<SubTexture2D>& subTexture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID);

		/// <summary>
		/// ͳ������
		/// </summary>
		struct Statistics
		{
			uint32_t DrawCalls = 0;	//���Ƶ��ô���
			uint32_t QuadCount = 0;	//�ı��θ���

			/// <summary>
			/// �����ܶ������
			/// </summary>
			/// <returns></returns>
			uint32_t GetTotalVertexCount() { return QuadCount * 4; }

			/// <summary>
			/// ��������������
			/// </summary>
			/// <returns></returns>
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static Statistics GetStats();

		/// <summary>
		/// ����ͳ������
		/// </summary>
		static void ResetStats();
	private:
		/// <summary>
		/// ��ʼ��һ����Ⱦ
		/// </summary>
		static void FlushAndReset(); 
	};
}