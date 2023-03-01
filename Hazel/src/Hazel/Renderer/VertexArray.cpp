#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platforms/OpenGL/OpenGLVertexArray.h"

namespace Hazel 
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:		//��API
				HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			case RendererAPI::API::OpenGL:	//OpenGL
				return CreateRef<OpenGLVertexArray>();	//������������
		}

		HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}