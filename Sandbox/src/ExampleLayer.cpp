#include "ExampleLayer.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer() :Layer("Example"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Hazel::VertexArray::Create();		//���������������

	float vertices[] = {
		//------λ��------   ---------��ɫ---------
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 1.0f, 1.0f,	//����
		 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 1.0f, 1.0f,	//����
		 0.0f,  0.5f, 0.0f,	1.0f, 1.0f, 0.0f, 1.0f,	//��
	};

	Hazel::Ref<Hazel::VertexBuffer> vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof(vertices));		//�������㻺��

	//���㻺��������
	Hazel::BufferLayout layout = {
		{Hazel::ShaderDataType::Float3, "a_Position"},	//λ��
		{Hazel::ShaderDataType::Float4, "a_Color"}		//��ɫ
	};

	vertexBuffer->SetLayout(layout);				//���ö��㻺��������
	m_VertexArray->AddVertexBuffer(vertexBuffer);	//���VBO��VAO

	unsigned int indices[3] = { 0,1,2 };		//��������

	Hazel::Ref<Hazel::IndexBuffer> indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));		//������������
	m_VertexArray->SetIndexBuffer(indexBuffer);													//����EBO��VAO

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

	m_Shader = Hazel::Shader::Create("TriangleColor", vertexSrc, fragmentSrc);	//������ɫ��

	//Square
	m_SquareVA = Hazel::VertexArray::Create();		//���������������

	float squareVertices[] = {
		//------λ��------  --��������--
		-0.5f, -0.5f, 0.0f,	0.0f, 0.0f,	//����0
		 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,	//����1
		-0.5f,  0.5f, 0.0f,	0.0f, 1.0f,	//����2
		 0.5f,  0.5f, 0.0f,	1.0f, 1.0f	//����3
	};

	Hazel::Ref<Hazel::VertexBuffer> squareVB = Hazel::VertexBuffer::Create(squareVertices, sizeof(squareVertices));	//�������㻺��

	squareVB->SetLayout({
		{Hazel::ShaderDataType::Float3, "a_Position"},	//λ��
		{Hazel::ShaderDataType::Float2, "a_TexCoord"},	//��������
		});
	m_SquareVA->AddVertexBuffer(squareVB);	//���VBO��VAO

	unsigned int squareIndices[] = { 0, 1, 2, 2, 1, 3 };		//��������

	Hazel::Ref<Hazel::IndexBuffer> squareIB = Hazel::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));	//������������
	m_SquareVA->SetIndexBuffer(squareIB);														//����EBO��VAO

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

	m_FlatColorShader = Hazel::Shader::Create("FlatColor", squareVertexSrc, squareFragmentSrc);	//������ɫ��

	auto textureShader = m_ShaderLibrary.Load("asserts/shaders/Texture.shader");		//������ɫ��

	m_Texture = Hazel::Texture2D::Create("asserts/textures/Checkerboard.png");			//��������
	m_ChernoLogoTexture = Hazel::Texture2D::Create("asserts/textures/ChernoLogo.png");	//��������

	textureShader->Bind();
	textureShader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnUpdate(Hazel::Timestep ts)
{
	m_CameraController.OnUpdate(ts);	//�������������

	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });	//����������ɫ
	Hazel::RenderCommand::Clear();										//���

	Hazel::Renderer::BeginScene(m_CameraController.GetCamera());		//��ʼ��Ⱦ����

	static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 20; x++) {
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;		//�����εı任����
			Hazel::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);		//�ύ��Ⱦָ��
		}
	}

	auto textureShader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	m_ChernoLogoTexture->Bind();
	Hazel::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//Triangle
	//Hazel::Renderer::Submit(m_Shader, m_VertexArray);	//�ύ��Ⱦָ��
	Hazel::Renderer::EndScene();						//������Ⱦ����
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Triangle Color", glm::value_ptr(m_SquareColor));	//��ɫ�༭UI
	ImGui::End();
}

void ExampleLayer::OnEvent(Hazel::Event& event)
{
	m_CameraController.OnEvent(event);	//��������¼�����
}