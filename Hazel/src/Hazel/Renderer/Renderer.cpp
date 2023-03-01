#include "hzpch.h"
#include "Renderer.h"

#include "Platforms/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace Hazel
{
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();		//场景数据

	void Renderer::Init()
	{
		HZ_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);	//设置视口大小
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();	//设置场景vp矩阵
	}
	
	void Renderer::EndScene()
	{
	
	}
	
	void Renderer::Submit(const Ref<Shader> shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);	//设置vp Uniform变量
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);										//设置model变换 Uniform变量

		vertexArray->Bind();						//绑定顶点数组
		RenderCommand::DrawIndexed(vertexArray);	//绘制
	}
}