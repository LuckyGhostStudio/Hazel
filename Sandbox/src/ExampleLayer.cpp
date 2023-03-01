#include "ExampleLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() :Layer("Example"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Hazel::VertexArray::Create();		//创建顶点数组对象

	float vertices[] = {
		//------位置------   ---------颜色---------
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 1.0f, 1.0f,	//左下
		 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 1.0f, 1.0f,	//右下
		 0.0f,  0.5f, 0.0f,	1.0f, 1.0f, 0.0f, 1.0f,	//上
	};

	Hazel::Ref<Hazel::VertexBuffer> vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));		//创建顶点缓冲

	//顶点缓冲区布局
	Hazel::BufferLayout layout = {
		{Hazel::ShaderDataType::Float3, "a_Position"},	//位置
		{Hazel::ShaderDataType::Float4, "a_Color"}		//颜色
	};

	vertexBuffer->SetLayout(layout);				//设置顶点缓冲区布局
	m_VertexArray->AddVertexBuffer(vertexBuffer);	//添加VBO到VAO

	unsigned int indices[3] = { 0,1,2 };		//顶点索引

	Hazel::Ref<Hazel::IndexBuffer> indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));		//创建索引缓冲
	m_VertexArray->SetIndexBuffer(indexBuffer);													//设置EBO到VAO

	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;					

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = v_Color;
			}
		)";

	m_Shader = Hazel::Shader::Create("TriangleColor", vertexSrc, fragmentSrc);	//创建着色器

	//Square
	m_SquareVA = Hazel::VertexArray::Create();		//创建顶点数组对象

	float squareVertices[] = {
		//------位置------  --纹理坐标--
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,	//左下0
		 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,	//右下1
		-0.5f,  0.5f, 0.0f,	0.0f, 1.0f,	//左上2
		 0.5f,  0.5f, 0.0f,	1.0f, 1.0f	//右上3
	};

	Hazel::Ref<Hazel::VertexBuffer> squareVB = Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));	//创建顶点缓冲

	squareVB->SetLayout({
		{Hazel::ShaderDataType::Float3, "a_Position"},	//位置
		{Hazel::ShaderDataType::Float2, "a_TexCoord"},	//纹理坐标
		});
	m_SquareVA->AddVertexBuffer(squareVB);	//添加VBO到VAO

	unsigned int squareIndices[] = { 0, 1, 2, 2, 1, 3 };		//顶点索引

	Hazel::Ref<Hazel::IndexBuffer> squareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));	//创建索引缓冲
	m_SquareVA->SetIndexBuffer(squareIB);														//设置EBO到VAO

	std::string squareVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;					

			void main()
			{
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
			}
		)";

	std::string squareFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader = Hazel::Shader::Create("FlatColor", squareVertexSrc, squareFragmentSrc);	//创建着色器

	auto textureShader = m_ShaderLibrary.Load("asserts/shaders/Texture.shader");		//加载着色器

	m_Texture = Hazel::Texture2D::Create("asserts/textures/Checkerboard.png");			//创建纹理
	m_ChernoLogoTexture = Hazel::Texture2D::Create("asserts/textures/ChernoLogo.png");	//创建纹理

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);	//更新相机控制器

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });	//设置清屏颜色
	Hazel::RenderCommand::Clear();										//清除

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());		//开始渲染场景

	static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;		//三角形的变换矩阵
			Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);		//提交渲染指令
		}
	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//Triangle
	//Hazel::Renderer::Submit(m_Shader, m_VertexArray);	//提交渲染指令
	Hazel::Renderer::EndScene();						//结束渲染场景
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Triangle Color", glm::value_ptr(m_SquareColor));	//颜色编辑UI
	ImGui::End();
}

void ExampleLayer::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);	//调用相机事件函数
}