#include "hzpch.h"
#include "Renderer.h"

#include "Platforms/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace Hazel
{
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();		//��������

	void Renderer::Init()
	{
		HZ_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);	//�����ӿڴ�С
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();	//���ó���vp����
	}
	
	void Renderer::EndScene()
	{
	
	}
	
	void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);	//����vp Uniform����
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);										//����model�任 Uniform����

		vertexArray->Bind();						//�󶨶�������
		RenderCommand::DrawIndexed(vertexArray);	//����
	}
}