#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Hazel
{
	/// <summary>
	/// ��Ⱦ��
	/// </summary>
	class Renderer
	{
	private:
		/// <summary>
		/// ��������
		/// </summary>
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;	//vp����
		};

		static Scope<SceneData> m_SceneData;	//��������
	public:
		/// <summary>
		/// ��ʼ����Ⱦ��
		/// </summary>
		static void Init();

		/// <summary>
		/// ��������ʱ����
		/// </summary>
		/// <param name="width">��</param>
		/// <param name="height">��</param>
		static void OnWindowResize(uint32_t width, uint32_t height);

		/// <summary>
		/// ��ʼ��Ⱦ���������ó�����������ɫ���������⣬�ƹ⣬�任�������...��
		/// </summary>
		/// <param name="camera">���</param>
		static void BeginScene(OrthographicCamera& camera);

		/// <summary>
		/// ������Ⱦ����
		/// </summary>
		static void EndScene();

		/// <summary>
		/// �ύ��Ⱦ����
		/// </summary>
		/// <param name="shader">��ɫ��</param>
		/// <param name="vertexArray">����Ⱦ��������</param>
		/// <param name="transform">�任����</param>
		static void Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}